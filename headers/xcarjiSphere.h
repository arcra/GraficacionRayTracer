/*
 * xcarjiSphere.h
 *
 *  Created on: Apr 4, 2013
 *      Author: arcra
 */
#ifndef XCARJISPHERE_H_
#define XCARJISPHERE_H_

#include "xcarVector.h"
#include "xcarjiISurface.h"

using namespace xcarGL;

namespace xcarjiRayTracing
{
	class xcarjiSphere : public xcarjiISurface {
		public:

			float radius;
			xcarVector center;

			xcarjiSphere(float radius, xcarVector center, bool drawIt=true);
			xcarjiSphere(float radius, xcarVector center, material m, bool drawIt=true);

			virtual bool isSurfaceHit(ray r, float& t);
			virtual xcarVector computeNormal(xcarVector point);
	};
}
#endif /* XCARJISPHERE_H_ */
