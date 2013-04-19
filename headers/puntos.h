#ifndef PUNTOS_H
#define PUNTOS_H

#include "Surfaces.h"
#include <vector>


using namespace RayTracing;
void getSurfaces(material mat, std::vector<ISurface*> &sur,float offsetX,float offsetY,float offsetZ);

void getFloor(material mat, material mat2,std::vector<ISurface*> &sur,float xmin, float zmin, float xmax, float zmax,float nMos);

#endif
