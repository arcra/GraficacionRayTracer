/*
 * ISurface.h
 *
 *  Created on: Abril 4, 2013
 *      Author: ontla
 */

#ifndef ISURFACE_H_
#define ISURFACE_H_

#include <iostream>
#include "Vector3D.h"
#include "Structures.h"

using namespace GL;

namespace RayTracing
{
	class ISurface {
		public:
			Vector3D normal;
			material mat;
			unsigned char* textureMap;
			unsigned char* bumpMap;
			int mapSizeX, mapSizeY;

			virtual bool isSurfaceHit(const ray r, float& t) = 0;
			virtual Vector3D computeNormal(Vector3D point) = 0;
			virtual void applyTransformation(float** m) = 0;
			virtual ~ISurface() {}
	};
}
#endif /* ISURFACE_H_ */