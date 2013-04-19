/*
 * Vector3D.cpp
 *
 *  Created on: Mar 28, 2013
 *      Author: arcra
 */

#include "Vector3D.h"
#include <cmath>
#include <iostream>

namespace GL
{

	Vector3D::Vector3D() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 1.0f;
	}

	Vector3D::Vector3D(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 1.0f;
	}

	Vector3D::Vector3D(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector3D::~Vector3D() {

	}

	Vector3D& Vector3D::operator+=(const Vector3D& other){

		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	Vector3D Vector3D::operator+(const Vector3D& other){
		//Vector3D newVector3D(this->x + other.x, this->y + other.y, this->z + other.z);
		Vector3D newVector3D(*this);
		return newVector3D += other;
	}


	Vector3D& Vector3D::operator-=(const Vector3D& other){

		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	Vector3D Vector3D::operator-(const Vector3D& other){
		Vector3D newVector3D(*this);
		newVector3D -= other;
		return newVector3D;
	}


	Vector3D& Vector3D::operator/=(const float k){

		this->x /= k;
		this->y /= k;
		this->z /= k;
		return *this;
	}

	Vector3D Vector3D::operator/(const float k){
		Vector3D newVector3D(*this);
		return newVector3D /= k;
	}


	Vector3D Vector3D::operator*(const float k){
		Vector3D newVector3D(*this);
		newVector3D.x *= k;
		newVector3D.y *= k;
		newVector3D.z *= k;
		return newVector3D;
	}

	float Vector3D::getMagnitude()
	{
		return sqrt(this->x*this->x +this->y*this->y + this->z*this->z);
	}

	Vector3D& Vector3D::normalize(){

		float magnitude = getMagnitude();
		if(magnitude == 0.0)
			return *this;
		this->x /= magnitude;
		this->y /= magnitude;
		this->z /= magnitude;

		return *this;
	}

	Vector3D Vector3D::getNormal(){

		float magnitude = getMagnitude();
		if(magnitude == 0.0)
			return Vector3D(0.0f, 0.0f, 0.0f);
		Vector3D normal(this->x/magnitude, this->y/magnitude, this->z/magnitude);

		return normal;
	}

	Vector3D Vector3D::crossProuct(const Vector3D& other){

		Vector3D result(this->y*other.z - other.y*this->z, this->z*other.x - other.z*this->x, this->x*other.y - other.x*this->y);
		return result;
	}

	float Vector3D::dotProduct(const Vector3D& other){

		return  this->x*other.x + this->y*other.y +this->z*other.z;
	}

	Vector3D operator*(const float k, const Vector3D& v){
		Vector3D newVector3D(v);
		newVector3D.x *= k;
		newVector3D.y *= k;
		newVector3D.z *= k;
		return newVector3D;
	}

	std::ostream& operator<<(std::ostream& stream, const Vector3D& v) {
	  return stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	}
}
