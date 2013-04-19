/*
 * TriangleFace.h
 *
 *  Created on: Apr 4, 2013
 *      Author: arcra
 */

#ifndef TRIANGLEFACE_H_
#define TRIANGLEFACE_H_

#include "ISurface.h"

namespace RayTracing {

	class TriangleFace: public RayTracing::ISurface {
		public:

			Vector3D v1;
			Vector3D v2;
			Vector3D v3;

			TriangleFace(Vector3D v1, Vector3D v2, Vector3D v3, bool drawIt=true);
			TriangleFace(Vector3D v1, Vector3D v2, Vector3D v3, material m, bool drawIt=true);

			virtual bool isSurfaceHit(ray r, float& t);
			virtual Vector3D computeNormal(Vector3D point);
			virtual void applyTransformation(float** m);
	};

} /* namespace RayTracing */
#endif /* TRIANGLEFACE_H_ */
