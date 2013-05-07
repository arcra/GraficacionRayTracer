/*
 * TriangleFace.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: arcra
 */

#include "TriangleFace.h"
#include "Operations.h"
#include <iostream>
#include <cstdlib>

using namespace std;

namespace RayTracing {

TriangleFace::TriangleFace(Vertex v1, Vertex v2, Vertex v3) : v1(v1.position), v2(v2.position), v3(v3.position) {

	this->v1 = Vertex(v1);
	this->v2 = v2;
	this->v3 = v3;

	this->normal = ((v2.position - v1.position).crossProuct(v3.position - v1.position)).getNormal();
}

TriangleFace::TriangleFace(Vertex v1, Vertex v2, Vertex v3, Material m) : v1(v1.position), v2(v2.position), v3(v3.position) {

	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->mat = m;

	this->normal = ((v2.position - v1.position).crossProuct(v3.position - v1.position)).getNormal();
}

bool TriangleFace::isSurfaceHit(ray r, float& t)
{
	if(round((r.s - r.e).dotProduct(this->computeNormal(Vector3D(0.0f, 0.0f, 0.0f))), 6) >= 0.0)
		return false;
	float a,b,c,d,e,f,g,h,i;

	Vector3D dir =  r.s - r.e;
	a = v1.position.x - v2.position.x;
	b = v1.position.y - v2.position.y;
	c = v1.position.z - v2.position.z;

	d = v1.position.x - v3.position.x;
	e = v1.position.y - v3.position.y;
	f = v1.position.z - v3.position.z;

	g = dir.x;
	h = dir.y;
	i = dir.z;

	float j,k,l;

	j = v1.position.x - r.e.x;
	k = v1.position.y - r.e.y;
	l = v1.position.z - r.e.z;

	float beta, gamma, M;
	float ei_minus_hf = e*i - h*f;
	float gf_minus_di = g*f - d*i;
	float dh_minus_eg = d*h - e*g;
	float bl_minus_kc = b*l - k*c;
	float jc_minus_al = j*c - a*l;
	float ak_minus_jb = a*k - j*b;


	M = a*ei_minus_hf + b*gf_minus_di + c*dh_minus_eg;

	t = (f*ak_minus_jb + e*jc_minus_al + d*bl_minus_kc)/-M;

	if(t <= 0.0f)
		return false;

	gamma = (i*ak_minus_jb + h*jc_minus_al + g*bl_minus_kc)/M;

	if(gamma < 0 || gamma > 1)
		return false;

	beta = (j*ei_minus_hf + k*gf_minus_di + l*dh_minus_eg)/M;

	if(beta < 0 || beta > (1.0 -gamma))
		return false;

	return true;
}

Vector3D TriangleFace::computeNormal(Vector3D point)
{
	return normal;
}

void TriangleFace::applyTransformation(float** m)
{
	multMatrixVector3D(m, this->v1.position, this->v1.position);
	multMatrixVector3D(m, this->v2.position, this->v2.position);
	multMatrixVector3D(m, this->v3.position, this->v3.position);

	this->normal = ((v2.position - v1.position).crossProuct(v3.position - v1.position)).getNormal();
}

void TriangleFace::getTextureCoords(Vector3D point, int& u, int& v)
{
	Vertex vert1(v1);
	Vertex vert2(v2);
	Vertex vert3(v3);

	float magA = (v2.position - v1.position).getMagnitude();
	float magB = (v3.position - v1.position).getMagnitude();
	float magC = (v3.position - v2.position).getMagnitude();

	if(magA >= magB && magA >= magC)
	{
		vert1 = v3;
		vert2 = v1;
		vert3 = v2;
	}
	else if(magB >= magA && magB >= magC)
	{
		vert1 = v2;
		vert2 = v3;
		vert3 = v1;
	}

	Vector3D pointVector = point - vert1.position;
	Vector3D axisVector = (vert3.position - vert1.position);
	Vector3D normalizedAxisVector = axisVector.getNormal();
	float scaling = pointVector.dotProduct(axisVector)/axisVector.getMagnitude();
	Vector3D projectedVector = scaling*normalizedAxisVector;

	float tu = vert1.tu + projectedVector.getMagnitude()/axisVector.getMagnitude()*(vert3.tu - vert1.tu);
	u = (int)round(tu*mat.sizeMapX, 0);

	axisVector = (vert3.position - vert1.position).crossProuct(computeNormal(point));
	normalizedAxisVector = axisVector.getNormal();
	scaling = (vert2.position - vert1.position).dotProduct(axisVector)/axisVector.getMagnitude();

	axisVector = scaling*normalizedAxisVector;
	normalizedAxisVector = axisVector.getNormal();
	scaling = pointVector.dotProduct(axisVector)/axisVector.getMagnitude();
	projectedVector = scaling*normalizedAxisVector;


	float tv = vert1.tv + projectedVector.getMagnitude()/axisVector.getMagnitude()*(vert2.tv - vert1.tv);
	v = (int)round(tv*mat.sizeMapY, 0);

}

TriangleFace::~TriangleFace()
{
	if(mat.textureMap)
		free(mat.textureMap);

	if(mat.bumpMap)
		free(mat.bumpMap);
}

} /* namespace RayTracing */
