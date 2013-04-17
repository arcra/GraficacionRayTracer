#ifndef XCCAMERA_H
#define XCCAMERA_H
#include "xcStructures.h"
#include "xcOperations.h"
#include "xcarVector.h"

using namespace xcarGL;

class xcCamera
{
 public: 
  xcCamera(xcarVector& pos,xcarVector& u,xcarVector& dir, bool o);
  ~xcCamera();
  void setCameraValues(xcarVector& pos, xcarVector& u, xcarVector& dir);
  void setCameraMatrix();
  void setView(float t, float b, float l, float r);
  void setProyectionMatrix(float frontPlane, float backPlane, float f);
  xcarVector position, up, lookAt;
  xcarVector cameraU, cameraV, cameraW;
  xcarVector cameraNormal;
  float** cameraMatrix;
  float** proyectionMatrix;
  // private:
  bool ortho;
  float top, bottom, left, right;
  float focalPoint;
};

#endif
