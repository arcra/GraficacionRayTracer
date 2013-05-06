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
		this->origin = Vector3D(0.0f, 1.0f, 0.0f);
	}

	Sphere::Sphere(float radius, Vector3D center, Material m)  : ISurface()
	{

		this->radius = radius;
		this->center = center;
		this->mat = m;
		this->origin = Vector3D(0.0f, 1.0f, 0.0f);
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
		multMatrixVector3D(m, this->origin, this->origin);
	}

	void Sphere::getTextureCoords(Vector3D point, int& u, int& v)
	{
		Vector3D planeProjection;
		float oppSideMag;
		float adySideMag;

		Vector3D surfNormal = (this->computeNormal(point) - this->origin).getNormal();

		planeProjection = surfNormal;
		planeProjection.y = 0.0f;

		oppSideMag = planeProjection.getMagnitude();
		adySideMag = surfNormal.y;

		float angleY = atan2(oppSideMag, adySideMag);


		planeProjection = surfNormal;
		planeProjection.x = 0.0f;

		oppSideMag = planeProjection.getMagnitude();
		adySideMag = surfNormal.x;

		float angleX = atan2(oppSideMag, adySideMag);

		u = (int)round(angleX*mat.sizeMapX/(2*PI), 0);
		v = (int)round(angleY*mat.sizeMapY/PI, 0);
	}

	Sphere::~Sphere()
	{
		if(mat.textureMap)
			free(mat.textureMap);

		if(mat.bumpMap)
			free(mat.bumpMap);
	}
}
