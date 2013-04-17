/*
 * xcarjiTriangleFace.h
 *
 *  Created on: Apr 4, 2013
 *      Author: arcra
 */

#ifndef XCARJITRIANGLEFACE_H_
#define XCARJITRIANGLEFACE_H_

#include "xcarjiISurface.h"

namespace xcarjiRayTracing {

	class xcarjiTriangleFace: public xcarjiRayTracing::xcarjiISurface {
		public:

			xcarVector v1;
			xcarVector v2;
			xcarVector v3;

			xcarjiTriangleFace(xcarVector v1, xcarVector v2, xcarVector v3, bool drawIt=true);
			xcarjiTriangleFace(xcarVector v1, xcarVector v2, xcarVector v3, material m, bool drawIt=true);

			virtual bool isSurfaceHit(ray r, float& t);
			virtual xcarVector computeNormal(xcarVector point);
	};

} /* namespace xcarjiRayTracing */
#endif /* XCARJITRIANGLEFACE_H_ */
