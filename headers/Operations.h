#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "Structures.h"
#include "Vector3D.h"

using namespace GL;

void multMatrixVector3D(float** m, const Vector3D a, Vector3D& r);
void multMatrix4Matrix4(float** a, float** b, float** r);
void matrixTranspose(float **m, float **t, int size);
float** getRotationMatrix(float angle_x, float angle_y, float angle_z);
float** getInverseRotationMatrix(float angle_x, float angle_y, float angle_z);
float** getTranslationMatrix(float tx, float ty, float tz);
float** getScalingMatrix(float sx, float sy, float sz);
unsigned char* readTextureFromBMP(char* filename, int &sizeX, int &sizeY);
unsigned char* readBumpMapFromBMP(char* filename, int &sizeX, int &sizeY);
void getTexturePixelToVector3D(int i, int j, Vector3D& component, unsigned char *textureBuffer, int sizeX, int sizeY);
void getNormalFromBumpMap(int u, int v, Vector3D& component, unsigned char *bumpMap, int sizeX, int sizeY, const Vector3D surfNormal);
float round(float number, unsigned char decimals=0);

#endif
