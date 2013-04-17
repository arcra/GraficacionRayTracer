/*
 * xcarjiSphere.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: arcra
 */

#include "xcarjiSphere.h"
#include "xcOperations.h"
#include <cmath>
#include <iostream>

using namespace std;

namespace xcarjiRayTracing
{

	xcarjiSphere::xcarjiSphere(float radius, xcarVector center, bool drawIt)  : xcarjiISurface(){

		this->radius = radius;
		this->center = center;
		this->drawable = drawIt;
	}

	xcarjiSphere::xcarjiSphere(float radius, xcarVector center, material m, bool drawIt)  : xcarjiISurface(){

		this->radius = radius;
		this->center = center;
		this->mat = m;
		this->drawable = drawIt;
	}


	bool xcarjiSphere::isSurfaceHit(ray r, float& t){
		xcarVector d = r.s - r.e;
		xcarVector e_c = r.e - center;

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

	xcarVector xcarjiSphere::computeNormal(xcarVector point){

		normal = (point - center).getNormal();
		return normal;
	}


}
