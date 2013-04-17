/*
 * xcarjiISurface.h
 *
 *  Created on: Abril 4, 2013
 *      Author: xcontla
 */

#ifndef XCARJIISURFACE_H_
#define XCARJIISURFACE_H_

#include <iostream>
#include "xcarVector.h"
#include "xcStructures.h"

using namespace xcarGL;

namespace xcarjiRayTracing
{
	class xcarjiISurface {
		public:
			xcarVector normal;
			material mat;
			bool drawable;

			virtual ~xcarjiISurface() {}
			virtual bool isSurfaceHit(const ray r, float& t) = 0;
			virtual xcarVector computeNormal(xcarVector point) = 0;

	};
}
#endif /* XCARJIISURFACE_H_ */
