/*
 * xcarjiRayTracer.h
 *
 *  Created on: Apr 5, 2013
 *      Author: arcra
 */

#ifndef XCARJIRAYTRACER_H_
#define XCARJIRAYTRACER_H_

#include <vector>
#include "xcCamera.h"
#include "xcarjiSurfaces.h"
#include "xcStructures.h"

using namespace std;

namespace xcarjiRayTracing {

class xcarjiRayTracer {
public:
	xcCamera *camera;
	vector<xcarjiISurface*> surfaces;
	vector<light> lights;
	unsigned char *rgbBuffer;


	xcarjiRayTracer(int width, int height, unsigned char *imageBuffer);
	void addLight(xcarVector position, float r, float g, float b);
	void addLight(float x, float y, float z, float r, float g, float b);
	void renderScence();
	bool pathToLightIsClear(xcarVector point, xcarVector lightPosition);
	bool findClosestIntersection(ray& currentRay, float& minT, unsigned int& surfaceIndex, bool ignoreNotDrawable=false);
	ray getBouncedRay(xcarjiISurface* surface, ray& r1, float t);
	void drawPixel(int i, int j, float r, float g, float b);
	~xcarjiRayTracer();

protected:
	unsigned int width;
	unsigned int height;
};

} /* namespace xcarjiRayTracing */
#endif /* XCARJIRAYTRACER_H_ */
