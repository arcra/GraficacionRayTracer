#ifndef XCSTRUCTS_H
#define XCSTRUCTS_H

#include <gtk/gtk.h>
#include "xcarVector.h"

using namespace xcarGL;

typedef struct
{
  xcarVector diffuse, specular, reflective;
  float shininess;
}material;

typedef struct
{
  xcarVector e;
  xcarVector s;
  
  float lifeSpan;
}ray;

typedef struct
{
	xcarVector point;
	xcarVector normal;
	material mat;
}rayBounce;

typedef struct
{
  xcarVector position;
  xcarVector rgb;
  float constant_attenuation_coeff;//= 0.25;
  float linear_attenuation_coeff;// = 0.003372407;
  float quadratic_attenuation_coeff;// = 0.000045492;

}light;



#endif

