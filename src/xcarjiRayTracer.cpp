/*
 * xcarjiRayTracer.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: arcra
 */

#include <cstdlib>
#include <cmath>
#include <stack>
#include "xcarjiRayTracer.h"
#include "xcStructures.h"

using namespace std;

namespace xcarjiRayTracing {

xcarjiRayTracer::xcarjiRayTracer(int width, int height, unsigned char *imageBuffer)
{
	this->width = width;
	this->height = height;
	this->rgbBuffer = imageBuffer;
}

void xcarjiRayTracer::addLight(xcarVector pos, float r, float g, float b)
{
	light l;
	l.position = pos;
	l.rgb.x = r;
	l.rgb.y = g;
	l.rgb.z = b;
	lights.push_back(l);
}

void xcarjiRayTracer::addLight(float x, float y, float z, float r, float g, float b)
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

void xcarjiRayTracer::renderScence(){

	unsigned int i, j, k, surfaceIndex;
	ray currentRay;
	rayBounce rayBounceInfo;
	rayBounce previousBounce;
	float us,vs,ws, minT, diffuseFactor;
	xcarVector lv, observerVec, h;
	xcarVector diffuse, specular, ambient, rgb;
	unsigned int lightCount;

	for(j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{

			us = camera->left + (camera->right - camera->left) * i/width;
			vs = camera->bottom + (camera->top - camera->bottom) * j/height;

			ws = camera->focalPoint;

			currentRay.e = camera->position;
			currentRay.s = xcarVector(us, vs, ws);
			if(currentRay.e.x == currentRay.s.x && currentRay.e.y == currentRay.s.y && currentRay.e.z == currentRay.s.z)
			{
				continue;
			}
			currentRay.lifeSpan = 1.0;
			stack<rayBounce> bounceStack;

			if(!findClosestIntersection(currentRay, minT, surfaceIndex, true))
				continue;

			ambient = surfaces[surfaceIndex]->mat.diffuse;

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

bool xcarjiRayTracer::pathToLightIsClear(xcarVector point, xcarVector lightPosition)
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

bool xcarjiRayTracer::findClosestIntersection(ray& currentRay, float& minT, unsigned int& surfaceIndex, bool ignoreNotDrawable)
{
	bool intersectionFound = false;
	unsigned int l;
	minT = FLT_MAX;
	float t;
	for(l = 0; l < surfaces.size(); l++){
		if(ignoreNotDrawable && !surfaces[l]->drawable)
			continue;
		if( surfaces[l]->isSurfaceHit(currentRay,t)){
			intersectionFound = true;
			if(t < minT){
				minT = t;
				surfaceIndex  = l;
			}
		}
	}
	return intersectionFound;
}

ray xcarjiRayTracer::getBouncedRay(xcarjiISurface *surface, ray& r1, float t)
{
	xcarVector d = r1.s - r1.e;
	xcarVector e2 = r1.e + t * d;
	xcarVector surfNormal = surface->computeNormal(e2);
	xcarVector reflectedVector = d - (2*d.dotProduct(surfNormal))*surfNormal;

	ray r2 = r1;

	r2.e = e2;
	r2.s = reflectedVector + e2;

	return r2;
}

void xcarjiRayTracer::drawPixel(int i, int j, float r, float g, float b)
{
	j = height - 1 - j;
	unsigned int ind = 3*(j*width + i);

	rgbBuffer[ind] = static_cast<unsigned char>(r*255);
	rgbBuffer[ind+1] = static_cast<unsigned char>(g*255);
	rgbBuffer[ind+2] = static_cast<unsigned char>(b*255);
}

xcarjiRayTracer::~xcarjiRayTracer()
{
	surfaces.clear();
	lights.clear();
	delete camera;
	free(rgbBuffer);
}

} /* namespace xcarjiRayTracing */
