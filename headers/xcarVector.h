/*
 * xcarVector.h
 *
 *  Created on: Mar 28, 2013
 *      Author: arcra
 */

#ifndef XCARVECTOR_H_
#define XCARVECTOR_H_

#include <iostream>

namespace xcarGL
{
	class xcarVector {
	public:
		float x, y, z, w;

		xcarVector();
		xcarVector(float, float, float);
		xcarVector(float, float, float, float);
		virtual ~xcarVector();
		xcarVector& operator+=(const xcarVector& other);
		xcarVector operator+(const xcarVector& other);
		xcarVector& operator-=(const xcarVector& other);
		xcarVector operator-(const xcarVector& other);
		xcarVector& operator/=(const float k);
		xcarVector operator/(const float k);
		xcarVector operator*(const float k);
		float getMagnitude();
		xcarVector& normalize();
		xcarVector getNormal();
		xcarVector crossProuct(const xcarVector& other);
		float dotProduct(const xcarVector& other);
	};

	xcarVector operator*(const float k, const xcarVector& v);
	std::ostream& operator<<(std::ostream&, const xcarVector&);
}

#endif /* XCARVECTOR_H_ */
