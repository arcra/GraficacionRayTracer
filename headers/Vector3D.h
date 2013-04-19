/*
 * Vector3D.h
 *
 *  Created on: Mar 28, 2013
 *      Author: arcra
 */

#ifndef Vector3D_H_
#define Vector3D_H_

#include <iostream>

namespace GL
{
	class Vector3D {
	public:
		float x, y, z, w;

		Vector3D();
		Vector3D(float, float, float);
		Vector3D(float, float, float, float);
		virtual ~Vector3D();
		Vector3D& operator+=(const Vector3D& other);
		Vector3D operator+(const Vector3D& other);
		Vector3D& operator-=(const Vector3D& other);
		Vector3D operator-(const Vector3D& other);
		Vector3D& operator/=(const float k);
		Vector3D operator/(const float k);
		Vector3D operator*(const float k);
		float getMagnitude();
		Vector3D& normalize();
		Vector3D getNormal();
		Vector3D crossProuct(const Vector3D& other);
		float dotProduct(const Vector3D& other);
	};

	Vector3D operator*(const float k, const Vector3D& v);
	std::ostream& operator<<(std::ostream&, const Vector3D&);
}

#endif /* Vector3D_H_ */
