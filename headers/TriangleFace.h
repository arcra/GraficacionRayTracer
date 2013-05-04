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

			Vertex v1;
			Vertex v2;
			Vertex v3;

			TriangleFace(Vertex v1, Vertex v2, Vertex v3);
			TriangleFace(Vertex v1, Vertex v2, Vertex v3, Material m);

			virtual bool isSurfaceHit(ray r, float& t);
			virtual Vector3D computeNormal(Vector3D point);
			virtual void applyTransformation(float** m);
			virtual void getTextureCoords(Vector3D point, int& u, int& v);

			virtual ~TriangleFace();
	};

} /* namespace RayTracing */
#endif /* TRIANGLEFACE_H_ */
