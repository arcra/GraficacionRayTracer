#ifndef PUNTOS_H
#define PUNTOS_H

#include "Surfaces.h"
#include <vector>


using namespace RayTracing;
void getSurfaces(Material mat, std::vector<ISurface*> &sur,float offsetX,float offsetY,float offsetZ);

void getFloor(Material mat, Material mat2,std::vector<ISurface*> &sur,float xmin, float zmin, float xmax, float zmax,float nMos);

#endif
