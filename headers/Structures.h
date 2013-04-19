#ifndef STRUCTS_H
#define STRUCTS_H

#include <gtk/gtk.h>
#include "Vector3D.h"

using namespace GL;

typedef struct
{
  Vector3D diffuse, specular, reflective;
  float shininess;
}material;

typedef struct
{
  Vector3D e;
  Vector3D s;
  
  float lifeSpan;
}ray;

typedef struct
{
	Vector3D point;
	Vector3D normal;
	material mat;
}rayBounce;

typedef struct
{
  Vector3D position;
  Vector3D rgb;
  float constant_attenuation_coeff;//= 0.25;
  float linear_attenuation_coeff;// = 0.003372407;
  float quadratic_attenuation_coeff;// = 0.000045492;

}light;



#endif

