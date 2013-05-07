/*
 * Sphere.h
 *
 *  Created on: Apr 4, 2013
 *      Author: arcra
 */
#ifndef SPHERE_H_
#define SPHERE_H_

#include "Vector3D.h"
#include "ISurface.h"

using namespace GL;

namespace RayTracing
{
	class Sphere : public ISurface {
		public:

			float radius;
			Vector3D center;

			Sphere(float radius, Vector3D center);
			Sphere(float radius, Vector3D center, Material m);

			virtual bool isSurfaceHit(ray r, float& t);
			virtual Vector3D computeNormal(Vector3D point);
			virtual void applyTransformation(float** m);
			virtual void getTextureCoords(Vector3D point, int& u, int& v);

			virtual ~Sphere();

		protected:
			Vector3D origin;
	};
}
#endif /* SPHERE_H_ */
