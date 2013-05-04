#ifndef STRUCTS_H
#define STRUCTS_H

#include <gtk/gtk.h>
#include "Vector3D.h"

using namespace GL;

typedef struct Vertex
{
	Vector3D position;
	float tu, tv;

	Vertex(Vector3D pos, float u = 0.0f, float v = 0.0f)
	{
		this->position = pos;
		this->tu = u;
		this->tv = v;
	}

}Vertex;

typedef struct Material
{
  Vector3D diffuse, specular, reflective;
  unsigned char *textureMap, *bumpMap;
  int sizeMapX, sizeMapY;
  float shininess;

  Material()
  {
	  this->textureMap = NULL;
	  this->bumpMap = NULL;
  }

}Material;

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
	Material mat;
	int surfaceIndex;
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

