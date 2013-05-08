/*
 * Sphere.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: arcra
 */

#include "Sphere.h"
#include "Operations.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

#define PI (3.141592653589793)

using namespace std;

namespace RayTracing
{

	Sphere::Sphere(float radius, Vector3D center)  : ISurface()
	{

		this->radius = radius;
		this->center = center;
		this->originX = Vector3D(1.0f, 0.0f, 0.0f);
		this->originY = Vector3D(0.0f, 1.0f, 0.0f);
	}

	Sphere::Sphere(float radius, Vector3D center, Material m)  : ISurface()
	{

		this->radius = radius;
		this->center = center;
		this->mat = m;
		this->originX = Vector3D(1.0f, 0.0f, 0.0f);
		this->originY = Vector3D(0.0f, 1.0f, 0.0f);
	}


	bool Sphere::isSurfaceHit(ray r, float& t)
	{
		Vector3D d = r.s - r.e;
		Vector3D e_c = r.e - center;

		float discrim =  (d.dotProduct(e_c) *  d.dotProduct(e_c)) -
		(d.dotProduct(d) * (e_c.dotProduct(e_c) - (radius*radius)));

		if(discrim < 0.0)
			return false;

		float a = round(((-1.0*d).dotProduct(e_c) + sqrt(discrim))/(d.dotProduct(d)), 4);
		float b = round(((-1.0*d).dotProduct(e_c) - sqrt(discrim))/(d.dotProduct(d)), 4);

		t = min(a, b);

		if(t <= 0.0)
			return false;

		return true;
	}

	Vector3D Sphere::computeNormal(Vector3D point)
	{

		normal = (point - center).getNormal();
		return normal;
	}

	void Sphere::applyTransformation(float** m)
	{
		multMatrixVector3D(m, this->originX, this->originX);
		multMatrixVector3D(m, this->originY, this->originY);
	}

	void Sphere::getTextureCoords(Vector3D point, int& u, int& v)
	{
		//FIND SPHERE ROTATION...

		float oppSideMag;
		float adySideMag;
		float angleY = 0.0f;
		float angleX = 0.0f;
		float **rotationMatrix;

		int i;

		Vector3D n = originX;

		oppSideMag = round(-n.z, 6);
		adySideMag = round(n.x, 6);

		if(oppSideMag != 0.0f)
		{
			if(adySideMag != 0.0f)
			{
				angleY = atan2(oppSideMag, adySideMag)*180/PI;
			}
			else
			{
				if(oppSideMag > 0.0f)
					angleY = 90.0f;
				else
					angleY = -90.0f;
			}

			rotationMatrix = getInverseRotationMatrix(0.0f, angleY, 0.0f);

			multMatrixVector3D(rotationMatrix, originY, n);

			for(i = 0; i < 4; i++)
				free(rotationMatrix[i]);
			free(rotationMatrix);
		}

		oppSideMag = round(n.z, 6);
		adySideMag = round(n.y, 6);

		if(oppSideMag != 0.0f)
		{
			if(adySideMag != 0.0f)
			{
				angleX = atan2(oppSideMag, adySideMag)*180/PI;
			}
			else
			{
				if(oppSideMag > 0.0f)
					angleX = 90.0f;
				else
					angleX = -90.0f;
			}
		}

		n = computeNormal(point);

		rotationMatrix = getInverseRotationMatrix(angleX, angleY, 0.0f);

		multMatrixVector3D(rotationMatrix, n, n);

		for(i = 0; i < 4; i++)
			free(rotationMatrix[i]);
		free(rotationMatrix);

		//FIND ANGLES FROM "UNROTATED" NORMAL

		oppSideMag = round(-n.z, 6);
		adySideMag = round(n.x, 6);

		if(oppSideMag != 0.0f)
		{
			if(adySideMag != 0.0f)
			{
				angleY = atan2(oppSideMag, adySideMag);
			}
			else
			{
				if(oppSideMag > 0.0f)
					angleY = PI/2.0f;
				else
					angleY = -PI/2.0f;
			}

			rotationMatrix = getInverseRotationMatrix(0.0f, angleY, 0.0f);

			multMatrixVector3D(rotationMatrix, n, n);

			for(i = 0; i < 4; i++)
				free(rotationMatrix[i]);
			free(rotationMatrix);
		}

		oppSideMag = round(n.z, 6);
		adySideMag = round(n.y, 6);

		if(oppSideMag != 0.0f)
		{
			if(adySideMag != 0.0f)
			{
				angleX = atan2(oppSideMag, adySideMag);
			}
			else
			{
				if(oppSideMag > 0.0f)
					angleX = PI/2.0f;
				else
					angleX = -PI/2.0f;
			}
		}

		u = (int)round(angleX*mat.sizeMapX/(2*PI), 0);
		v = mat.sizeMapY -1 - (int)round((angleY-PI/2.0f)*(mat.sizeMapY-1)/PI, 0);
	}

	Sphere::~Sphere()
	{
		if(mat.textureMap)
			free(mat.textureMap);

		if(mat.bumpMap)
			free(mat.bumpMap);
	}
}
