#include "Camera.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

Camera::Camera(Vector3D& pos, Vector3D& u, Vector3D& dir, bool o)
{
  position = pos;
  up = u;
  lookAt = dir;
  ortho = o;
  cameraMatrix = (float**)malloc(sizeof(float*)*4);
  proyectionMatrix = (float**)malloc(sizeof(float*)*4);

  for(int j = 0; j < 4; j++){
    cameraMatrix[j] = (float*)malloc(sizeof(float)*4);
    proyectionMatrix[j] = (float*)malloc(sizeof(float)*4);
  }
  
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++){
      cameraMatrix[j][i] = 0.0;
      proyectionMatrix[i][j] = 0.0;
    }

  setCameraValues(pos,u,dir);
}

Camera::~Camera()
{
  for(int i = 0; i < 4 ; i++)
    {
      free(cameraMatrix[i]);
      free(proyectionMatrix[i]);
    }
  free(cameraMatrix);
  free(proyectionMatrix);  
}


void Camera::setCameraValues(Vector3D& pos, Vector3D& u, Vector3D& dir)
{
  position = pos;
  up = u;
  lookAt = dir;

  cameraW = (position - lookAt).normalize();
  cameraU = up.crossProuct(cameraW).normalize();
  cameraV = cameraW.crossProuct(cameraU);

  cameraNormal = -1*cameraW;

  setCameraMatrix();
}

void Camera::setCameraMatrix()
{
  Vector3D e1(1.0f, 0.0f, 0.0f);
  Vector3D e2(0.0f, 1.0f, 0.0f);
  Vector3D e3(0.0f, 0.0f, 1.0f);
  
  cameraMatrix[0][0] = e1.dotProduct(cameraU);
  cameraMatrix[0][1] = e1.dotProduct(cameraV);
  cameraMatrix[0][2] = e1.dotProduct(cameraW);
  cameraMatrix[0][3] = 0.0f;

  cameraMatrix[1][0] = e2.dotProduct(cameraU);
  cameraMatrix[1][1] = e2.dotProduct(cameraV);
  cameraMatrix[1][2] = e2.dotProduct(cameraW);
  cameraMatrix[1][3] = 0.0f;

  cameraMatrix[2][0] = e3.dotProduct(cameraU);
  cameraMatrix[2][1] = e3.dotProduct(cameraV);
  cameraMatrix[2][2] = e3.dotProduct(cameraW);
  cameraMatrix[2][3] = 0.0f;

  cameraMatrix[3][0] = 0.0f;
  cameraMatrix[3][1] = 0.0f;
  cameraMatrix[3][2] = 0.0f;
  cameraMatrix[3][3] = 1.0f;

  //printMatrix(cameraMatrix,4);

  float** transpose;

  transpose = (float**)malloc(sizeof(float*)*4);
  
  for(int j = 0; j < 4; j++){
    transpose[j] = (float*)malloc(sizeof(float)*4);
  }
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      transpose[j][i] = 0.0f;

  matrixTranspose(cameraMatrix,transpose,4);
  Vector3D temp;
  multMatrixVector3D(transpose,position,temp);
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      cameraMatrix[i][j] = transpose[i][j];

  cameraMatrix[0][3] = (-1.0f*temp.x);
  cameraMatrix[1][3] = (-1.0f*temp.y);
  cameraMatrix[2][3] = (-1.0f*temp.z);
  cameraMatrix[3][3] = 1.0f;
  cameraMatrix[3][2] = 0.0f;
  cameraMatrix[3][1] = 0.0f;
  cameraMatrix[3][0] = 0.0f;

  //cout << "camera" << endl;
  //printMatrix(cameraMatrix,4);

  for(int i = 0; i < 4 ; i++)
    free(transpose[i]);
  free(transpose);
 
}

void Camera::setProyectionMatrix(float frontPlane, float backPlane, float f)
{

	cout << "Camera mode: ";

  float bfb = backPlane/(backPlane - frontPlane);
  if(ortho)
    {
      proyectionMatrix[0][0] = 1.0f;
      proyectionMatrix[0][1] = 0.0f;
      proyectionMatrix[0][2] = 0.0f;
      proyectionMatrix[0][3] = 0.0f;

      proyectionMatrix[1][0] = 0.0f;
      proyectionMatrix[1][1] = 1.0f;
      proyectionMatrix[1][2] = 0.0f;
      proyectionMatrix[1][3] = 0.0f;
  
      proyectionMatrix[2][0] = 0.0f; 
      proyectionMatrix[2][1] = 0.0f;
      proyectionMatrix[2][2] = bfb;//(backPlane/(backPlane - frontPlane));
      proyectionMatrix[2][3] = -f*bfb;//;(-f*backPlane/(backPlane - frontPlane));

      proyectionMatrix[3][0] = 0.0f;
      proyectionMatrix[3][1] = 0.0f;
      proyectionMatrix[3][2] = 0.0f;
      proyectionMatrix[3][3] = 1.0f;
      cout << "ortho" << endl;
    }else
    {
      proyectionMatrix[0][0] = f/right;
      proyectionMatrix[0][1] = 0.0f;
      proyectionMatrix[0][2] = 0.0f;
      proyectionMatrix[0][3] = 0.0f;

      proyectionMatrix[1][0] = 0.0f;
      proyectionMatrix[1][1] = f/top;
      proyectionMatrix[1][2] = 0.0f;
      proyectionMatrix[1][3] = 0.0f;
  
      proyectionMatrix[2][0] = 0.0f; 
      proyectionMatrix[2][1] = 0.0f;
      proyectionMatrix[2][2] = bfb;
      proyectionMatrix[2][3] = -f*bfb;

      proyectionMatrix[3][0] = 0.0f;
      proyectionMatrix[3][1] = 0.0f;
      proyectionMatrix[3][2] = 1.0/f;
      proyectionMatrix[3][3] = 0.0f;
      cout << "perspective" << endl;
    }

  //printMatrix(proyectionMatrix,4);
  
}

void Camera::setView(float t, float b, float l, float r)
{
  top = t;
  bottom = b;
  left = l;
  right = r;
}
