#ifndef CAMERA_H
#define CAMERA_H
#include "Structures.h"
#include "Operations.h"
#include "Vector3D.h"

using namespace GL;

class Camera
{
 public: 
  Camera(Vector3D& pos,Vector3D& u,Vector3D& dir, bool o);
  ~Camera();
  void setCameraValues(Vector3D& pos, Vector3D& u, Vector3D& dir);
  void setCameraMatrix();
  void setView(float t, float b, float l, float r);
  void setProyectionMatrix(float frontPlane, float backPlane, float f);
  Vector3D position, up, lookAt;
  Vector3D cameraU, cameraV, cameraW;
  Vector3D cameraNormal;
  float** cameraMatrix;
  float** proyectionMatrix;
  // private:
  bool ortho;
  float top, bottom, left, right;
  float focalPoint;
};

#endif
