/*
 * arxcVector.cpp
 *
 *  Created on: Mar 28, 2013
 *      Author: arcra
 */

#include "xcarVector.h"
#include <cmath>
#include <iostream>

namespace xcarGL
{

	xcarVector::xcarVector() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 1.0f;
	}

	xcarVector::xcarVector(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 1.0f;
	}

	xcarVector::xcarVector(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	xcarVector::~xcarVector() {

	}

	xcarVector& xcarVector::operator+=(const xcarVector& other){

		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	xcarVector xcarVector::operator+(const xcarVector& other){
		//xcarVector newVector(this->x + other.x, this->y + other.y, this->z + other.z);
		xcarVector newVector(*this);
		return newVector += other;
	}


	xcarVector& xcarVector::operator-=(const xcarVector& other){

		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	xcarVector xcarVector::operator-(const xcarVector& other){
		xcarVector newVector(*this);
		newVector -= other;
		return newVector;
	}


	xcarVector& xcarVector::operator/=(const float k){

		this->x /= k;
		this->y /= k;
		this->z /= k;
		return *this;
	}

	xcarVector xcarVector::operator/(const float k){
		xcarVector newVector(*this);
		return newVector /= k;
	}


	xcarVector xcarVector::operator*(const float k){
		xcarVector newVector(*this);
		newVector.x *= k;
		newVector.y *= k;
		newVector.z *= k;
		return newVector;
	}

	float xcarVector::getMagnitude()
	{
		return sqrt(this->x*this->x +this->y*this->y + this->z*this->z);
	}

	xcarVector& xcarVector::normalize(){

		float magnitude = getMagnitude();
		if(magnitude == 0.0)
			return *this;
		this->x /= magnitude;
		this->y /= magnitude;
		this->z /= magnitude;

		return *this;
	}

	xcarVector xcarVector::getNormal(){

		float magnitude = getMagnitude();
		if(magnitude == 0.0)
			return xcarVector(0.0f, 0.0f, 0.0f);
		xcarVector normal(this->x/magnitude, this->y/magnitude, this->z/magnitude);

		return normal;
	}

	xcarVector xcarVector::crossProuct(const xcarVector& other){

		xcarVector result(this->y*other.z - other.y*this->z, this->z*other.x - other.z*this->x, this->x*other.y - other.x*this->y);
		return result;
	}

	float xcarVector::dotProduct(const xcarVector& other){

		return  this->x*other.x + this->y*other.y +this->z*other.z;
	}

	xcarVector operator*(const float k, const xcarVector& v){
		xcarVector newVector(v);
		newVector.x *= k;
		newVector.y *= k;
		newVector.z *= k;
		return newVector;
	}

	std::ostream& operator<<(std::ostream& stream, const xcarVector& v) {
	  return stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	}
}
