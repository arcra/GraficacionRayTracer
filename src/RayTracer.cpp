/*
 * RayTracer.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: arcra
 */

#include <glib/gtypes.h>
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <stack>
#include "RayTracer.h"
#include "Structures.h"

using namespace std;

namespace RayTracing {

RayTracer::RayTracer(int width, int height)
{
	this->width = width;
	this->height = height;

	this->rgbBuffer = (guchar*)malloc(sizeof(guchar)*this->width * this->height * 3);
	unsigned int x, y;
	unsigned char *pos;
	pos = this->rgbBuffer;
	for (y = 0; y < this->height; y++)
	{
		for (x = 0; x < this->width; x++)
		{
			*pos++ = 0;
			*pos++ = 0;
			*pos++ = 0;
		}
	}

	this->loadIdentity();
}

void RayTracer::addLight(Vector3D pos, float r, float g, float b)
{
	light l;
	l.position = pos;
	l.rgb.x = r;
	l.rgb.y = g;
	l.rgb.z = b;
	lights.push_back(l);
}

void RayTracer::addLight(float x, float y, float z, float r, float g, float b)
{
	light l;
	l.position.x = x;
	l.position.y = y;
	l.position.z = z;
	l.rgb.x = r;
	l.rgb.y = g;
	l.rgb.z = b;
	lights.push_back(l);
}

void RayTracer::addSurface(ISurface* surf)
{
	surf->applyTransformation(this->transformationMatrix);
	this->surfaces.push_back(surf);
}

void RayTracer::renderScence()
{
	unsigned int i, j, k, surfaceIndex;
	ray currentRay;
	rayBounce rayBounceInfo;
	rayBounce previousBounce;
	float us,vs,ws, minT, diffuseFactor;
	Vector3D lv, observerVec, h;
	Vector3D diffuse, specular, ambient, rgb;
	unsigned int lightCount;

	for(j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			us = camera->left + (camera->right - camera->left) * i/width;
			vs = camera->bottom + (camera->top - camera->bottom) * j/height;

			ws = camera->focalPoint;

			currentRay.e = camera->position;
			currentRay.s = Vector3D(us, vs, ws);
			if(currentRay.e.x == currentRay.s.x && currentRay.e.y == currentRay.s.y && currentRay.e.z == currentRay.s.z)
				continue;
			currentRay.lifeSpan = 1.0;
			stack<rayBounce> bounceStack;

			if(!findClosestIntersection(currentRay, minT, surfaceIndex))
				continue;

			Vector3D matDiffuse;
			if(surfaces[surfaceIndex]->mat.textureMap)
			{
				matDiffuse
				//Vector3D matDiffuse = map.text;
			}
			else
			{
				matDiffuse = surfaces[surfaceIndex]->mat.diffuse;
			}

			ambient = matDiffuse;

			rayBounceInfo.point = currentRay.e + minT*(currentRay.s - currentRay.e);
			rayBounceInfo.point.x = round(rayBounceInfo.point.x, 4);
			rayBounceInfo.point.y = round(rayBounceInfo.point.y, 4);
			rayBounceInfo.point.z = round(rayBounceInfo.point.z, 4);
			rayBounceInfo.normal = surfaces[surfaceIndex]->computeNormal(rayBounceInfo.point);
			rayBounceInfo.mat = surfaces[surfaceIndex]->mat;

			bounceStack.push(rayBounceInfo);

			currentRay.lifeSpan *= max(max(rayBounceInfo.mat.reflective.x, rayBounceInfo.mat.reflective.y), rayBounceInfo.mat.reflective.z);
			currentRay = getBouncedRay(surfaces[surfaceIndex], currentRay, minT);


			while(currentRay.lifeSpan > 0.1 && findClosestIntersection(currentRay, minT, surfaceIndex))
			{
				rayBounceInfo.point = currentRay.e + minT*(currentRay.s - currentRay.e);
				rayBounceInfo.point.x = round(rayBounceInfo.point.x, 4);
				rayBounceInfo.point.y = round(rayBounceInfo.point.y, 4);
				rayBounceInfo.point.z = round(rayBounceInfo.point.z, 4);
				rayBounceInfo.normal = surfaces[surfaceIndex]->computeNormal(rayBounceInfo.point);
				rayBounceInfo.mat = surfaces[surfaceIndex]->mat;

				bounceStack.push(rayBounceInfo);

				currentRay.lifeSpan *= max(max(rayBounceInfo.mat.reflective.x, rayBounceInfo.mat.reflective.y), rayBounceInfo.mat.reflective.z);
				currentRay = getBouncedRay(surfaces[surfaceIndex], currentRay, minT);
			}

			previousBounce.mat.reflective.x = 0.0f;
			previousBounce.mat.reflective.y = 0.0f;
			previousBounce.mat.reflective.z = 0.0f;

			previousBounce.mat.diffuse.x = 0.0f;
			previousBounce.mat.diffuse.y = 0.0f;
			previousBounce.mat.diffuse.z = 0.0f;

			previousBounce.mat.specular.x = 0.0f;
			previousBounce.mat.specular.y = 0.0f;
			previousBounce.mat.specular.z = 0.0f;

			while(!bounceStack.empty())
			{
				rayBounceInfo = bounceStack.top();
				bounceStack.pop();
				diffuse.x = diffuse.y = diffuse.z = 0.0f;
				specular.x = specular.y = specular.z = 0.0f;

				if(lights.size() > 0)
				{
					lightCount = 0;
					for(k = 0; k < lights.size(); k++)
					{
						if(pathToLightIsClear(rayBounceInfo.point, lights[k].position))
						{
							lv = (lights[k].position - rayBounceInfo.point).normalize();

							diffuseFactor = max(rayBounceInfo.normal.dotProduct(lv), 0.0f);
							observerVec = (camera->position - rayBounceInfo.point).normalize();
							h = 2*max(rayBounceInfo.normal.dotProduct(lv), 0.0f)*rayBounceInfo.normal - lv;

							diffuse.x += lights[k].rgb.x*rayBounceInfo.mat.diffuse.x*diffuseFactor;
							diffuse.y += lights[k].rgb.y*rayBounceInfo.mat.diffuse.y*diffuseFactor;
							diffuse.z += lights[k].rgb.z*rayBounceInfo.mat.diffuse.z*diffuseFactor;

							specular.x += lights[k].rgb.x*rayBounceInfo.mat.specular.x*pow(max(observerVec.dotProduct(h), 0.0f), rayBounceInfo.mat.shininess);
							specular.y += lights[k].rgb.y*rayBounceInfo.mat.specular.y*pow(max(observerVec.dotProduct(h), 0.0f), rayBounceInfo.mat.shininess);
							specular.z += lights[k].rgb.z*rayBounceInfo.mat.specular.z*pow(max(observerVec.dotProduct(h), 0.0f), rayBounceInfo.mat.shininess);


							lightCount++;
						}
					}
					if(lightCount > 0)
					{
						diffuse.x /= lightCount;
						diffuse.y /= lightCount;
						diffuse.z /= lightCount;

						specular.x /= lightCount;
						specular.y /= lightCount;
						specular.z /= lightCount;
					}
				}

				previousBounce.mat.diffuse.x = diffuse.x*(1-rayBounceInfo.mat.reflective.x) + previousBounce.mat.diffuse.x*rayBounceInfo.mat.reflective.x;
				previousBounce.mat.diffuse.y = diffuse.y*(1-rayBounceInfo.mat.reflective.y) + previousBounce.mat.diffuse.y*rayBounceInfo.mat.reflective.y;
				previousBounce.mat.diffuse.z = diffuse.z*(1-rayBounceInfo.mat.reflective.z) + previousBounce.mat.diffuse.z*rayBounceInfo.mat.reflective.z;

				previousBounce.mat.specular.x = specular.x;
				previousBounce.mat.specular.y = specular.y;
				previousBounce.mat.specular.z = specular.z;

				previousBounce.mat.reflective = rayBounceInfo.mat.reflective;

				previousBounce.point = rayBounceInfo.point;
				previousBounce.normal = rayBounceInfo.normal;

			}

			rgb.x = (ambient.x*0.3f + previousBounce.mat.diffuse.x*0.4f)*(1 - previousBounce.mat.reflective.x) + previousBounce.mat.diffuse.x*0.7f*previousBounce.mat.reflective.x + previousBounce.mat.specular.x*0.3f;
			rgb.y = (ambient.y*0.3f + previousBounce.mat.diffuse.y*0.4f)*(1 - previousBounce.mat.reflective.y) + previousBounce.mat.diffuse.y*0.7f*previousBounce.mat.reflective.y + previousBounce.mat.specular.y*0.3f;
			rgb.z = (ambient.z*0.3f + previousBounce.mat.diffuse.z*0.4f)*(1 - previousBounce.mat.reflective.z) + previousBounce.mat.diffuse.z*0.7f*previousBounce.mat.reflective.z + previousBounce.mat.specular.z*0.3f;

			drawPixel(i,j,rgb.x,rgb.y,rgb.z);
		}
	}
}

unsigned char* RayTracer::getImageBuffer()
{

	return this->rgbBuffer;
}

void  RayTracer::loadIdentity()
{
	int i;
	float** temp;
	while(!this->matrixStack.empty())
	{
		temp = this->matrixStack.top();
		this->matrixStack.pop();
		for(i = 0; i < 4; i++)
			free(temp[i]);
		free(temp);
	}

	temp = (float**)malloc(4*sizeof(float*));

	for(i = 0; i < 4; i++){
		temp[i] = (float*)malloc(4*sizeof(float));
		for(int j = 0; j < 4; j++){
			temp[i][j] = static_cast<float>(i == j);
		}
	}
	this->matrixStack.push(temp);
	this->transformationMatrix = this->matrixStack.top();
}

void RayTracer::rotate(float angle_x, float angle_y, float angle_z)
{
	float** rotationMatrix = getRotationMatrix(angle_x, angle_y, angle_z);
	multMatrix4Matrix4(rotationMatrix, this->transformationMatrix, this->transformationMatrix);
}

void RayTracer::scale(float sx, float sy, float sz)
{
	float** scalingMatrix = getScalingMatrix(sx, sy, sz);
	multMatrix4Matrix4(scalingMatrix, this->transformationMatrix, this->transformationMatrix);
}

void RayTracer::translate(float tx, float ty, float tz)
{
	float** translationMatrix = getTranslationMatrix(tx, ty, tz);
	multMatrix4Matrix4(translationMatrix, this->transformationMatrix, this->transformationMatrix);
}

void RayTracer::pushMatrix()
{
	int i,j;

	float **m = (float**)malloc(4*sizeof(float*));

	for(i = 0; i < 4; i++)
	{
		m[i] = (float*)malloc(4*sizeof(float));
		for(j = 0; j < 4; j++)
			m[i][j] = this->transformationMatrix[i][j];
	}
	this->matrixStack.push(m);
}

void RayTracer::popMatrix()
{
	int i, j;
	float** temp;
	temp = this->matrixStack.top();
	this->matrixStack.pop();

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			this->transformationMatrix[i][j] = temp[i][j];

	for(i = 0; i < 4; i++)
		free(temp[i]);
	free(temp);
}


bool RayTracer::pathToLightIsClear(Vector3D point, Vector3D lightPosition)
{
	ray pathRay;
	pathRay.e = point;
	pathRay.s = lightPosition;
	unsigned int l;
	float t;
	for(l = 0; l < surfaces.size(); l++){
		if( surfaces[l]->isSurfaceHit(pathRay,t)){
			if(t < 1.0)
				return false;
		}
	}
	return true;
}

bool RayTracer::findClosestIntersection(ray& currentRay, float& minT, unsigned int& surfaceIndex)
{
	bool intersectionFound = false;
	unsigned int l;
	minT = FLT_MAX;
	float t;
	for(l = 0; l < surfaces.size(); l++){
		if( surfaces[l]->isSurfaceHit(currentRay,t) && surfaces[l]->computeNormal(currentRay.e + t*(currentRay.s - currentRay.e)).dotProduct(currentRay.e - currentRay.s) > 0.0f){
			intersectionFound = true;
			if(t < minT){
				minT = t;
				surfaceIndex = l;
			}
		}
	}
	return intersectionFound;
}

ray RayTracer::getBouncedRay(ISurface *surface, ray& r1, float t)
{
	Vector3D d = r1.s - r1.e;
	Vector3D e2 = r1.e + t * d;
	Vector3D surfNormal = surface->computeNormal(e2);
	Vector3D reflectedVector3D = d - (2*d.dotProduct(surfNormal))*surfNormal;

	ray r2 = r1;

	r2.e = e2;
	r2.s = reflectedVector3D + e2;

	return r2;
}

void RayTracer::drawPixel(int i, int j, float r, float g, float b)
{
	j = height - 1 - j;
	unsigned int ind = 3*(j*width + i);

	rgbBuffer[ind] = static_cast<unsigned char>(r*255);
	rgbBuffer[ind+1] = static_cast<unsigned char>(g*255);
	rgbBuffer[ind+2] = static_cast<unsigned char>(b*255);
}

RayTracer::~RayTracer()
{
	surfaces.clear();
	lights.clear();
	delete camera;
	free(rgbBuffer);
}

} /* namespace RayTracing */
