/*
 * RayTracer.h
 *
 *  Created on: Apr 5, 2013
 *      Author: arcra
 */

#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <vector>
#include <stack>
#include "Camera.h"
#include "Surfaces.h"
#include "Structures.h"

using namespace std;

namespace RayTracing {

class RayTracer {
public:
	Camera *camera;
	vector<light> lights;

	RayTracer(int width, int height);
	void addLight(Vector3D position, float r, float g, float b);
	void addLight(float x, float y, float z, float r, float g, float b);
	void addSurface(ISurface* surf);
	void renderScence();
	unsigned char* getImageBuffer();
	void loadIdentity();
	void rotate(float angle_x, float angle_y, float angle_z);
	void scale(float sx, float sy, float sz);
	void translate(float tx, float ty, float tz);

	~RayTracer();

protected:

	unsigned int width;
	unsigned int height;
	unsigned char *rgbBuffer;
	float** transgormationMatrix;
	stack<float**> matrixStack;
	vector<ISurface*> surfaces;

	void pushMatrix();
	void popMatrix();

	bool pathToLightIsClear(Vector3D point, Vector3D lightPosition);
	bool findClosestIntersection(ray& currentRay, float& minT, unsigned int& surfaceIndex);
	ray getBouncedRay(ISurface* surface, ray& r1, float t);
	void drawPixel(int i, int j, float r, float g, float b);
};

} /* namespace RayTracing */
#endif /* RAYTRACER_H_ */
