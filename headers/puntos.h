/*#ifndef PUNTOS_H
#define PUNTOS_H
//#include "xcarjiISurface.h"
#include "xcarjiSurfaces.h"
#include <vector>

using namespace xcarjiRayTracing;

void getSurfaces(material mat, std::vector<xcarjiISurface*> &sur);

#endif
*/
#ifndef PUNTOS_H
#define PUNTOS_H

#include "xcarjiSurfaces.h"
#include <vector>


using namespace xcarjiRayTracing;
void getSurfaces(material mat, std::vector<xcarjiISurface*> &sur,float offsetX,float offsetY,float offsetZ);

void getFloor(material mat, material mat2,std::vector<xcarjiISurface*> &sur,float xmin, float zmin, float xmax, float zmax,float nMos);

#endif
