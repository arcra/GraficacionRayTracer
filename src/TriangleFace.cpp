/*
 * TriangleFace.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: arcra
 */

#include "TriangleFace.h"
#include "Operations.h"
#include <iostream>

using namespace std;

namespace RayTracing {

TriangleFace::TriangleFace(Vector3D v1, Vector3D v2, Vector3D v3) {

	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
}

TriangleFace::TriangleFace(Vector3D v1, Vector3D v2, Vector3D v3, material m) {

	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->mat = m;
}

bool TriangleFace::isSurfaceHit(ray r, float& t)
{
	if((r.s - r.e).dotProduct(this->computeNormal(Vector3D(0.0f, 0.0f, 0.0f))) == 0.0)
		return false;
	float a,b,c,d,e,f,g,h,i;

	Vector3D dir =  r.s - r.e;
	a = v1.x - v2.x;
	b = v1.y - v2.y;
	c = v1.z - v2.z;

	d = v1.x - v3.x;
	e = v1.y - v3.y;
	f = v1.z - v3.z;

	g = dir.x;
	h = dir.y;
	i = dir.z;

	float j,k,l;

	j = v1.x - r.e.x;
	k = v1.y - r.e.y;
	l = v1.z - r.e.z;

	float beta, gamma, M, ta;
	float ei_minus_hf = e*i - h*f;
	float gf_minus_di = g*f - d*i;
	float dh_minus_eg = d*h - e*g;
	float bl_minus_kc = b*l - k*c;
	float jc_minus_al = j*c - a*l;
	float ak_minus_jb = a*k - j*b;


	M = a*ei_minus_hf + b*gf_minus_di + c*dh_minus_eg;

	ta = (f*ak_minus_jb + e*jc_minus_al + d*bl_minus_kc)/-M;

	if(ta <= 0.0)
		return false;

	gamma = (i*ak_minus_jb + h*jc_minus_al + g*bl_minus_kc)/M;

	if(gamma < 0 || gamma > 1)
		return false;

	beta = (j*ei_minus_hf + k*gf_minus_di + l*dh_minus_eg)/M;

	if(beta < 0 || beta > (1.0 -gamma))
		return false;

	t = ta;

	return true;
}

Vector3D TriangleFace::computeNormal(Vector3D point)
{
	normal = ((v2 - v1).crossProuct(v3 - v1)).getNormal();
	return normal;
}

void TriangleFace::applyTransformation(float** m)
{
	multMatrixVector3D(m, this->v1, this->v1);
	multMatrixVector3D(m, this->v2, this->v2);
	multMatrixVector3D(m, this->v3, this->v3);
}

} /* namespace RayTracing */
