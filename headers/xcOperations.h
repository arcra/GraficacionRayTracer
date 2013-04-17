#ifndef XCOPERATIONS_H
#define XCOPERATIONS_H
#include "xcStructures.h"
#include "xcarVector.h"

using namespace xcarGL;

void multMatrixVector(float** m, const xcarVector& a, xcarVector& r);
void multMatrix4Matrix4(float** a, float** b, float** r);
void matrixTranspose(float **m, float **t, int size);
unsigned char* readBMP(char* filename, int &sizeX, int &sizeY);
float round(float number, unsigned char decimals=0);

#endif
