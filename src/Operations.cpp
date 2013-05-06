
#include "Operations.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define PI (3.141592653589793)
using namespace std;


void multMatrixVector3D(float** m, const Vector3D a, Vector3D& r)
{
  Vector3D temp = a;
  r.x = m[0][0] * temp.x + m[0][1] * temp.y + m[0][2] * temp.z + m[0][3] * temp.w;
  r.y = m[1][0] * temp.x + m[1][1] * temp.y + m[1][2] * temp.z + m[1][3] * temp.w;
  r.z = m[2][0] * temp.x + m[2][1] * temp.y + m[2][2] * temp.z + m[2][3] * temp.w;
  r.w = m[3][0] * temp.x + m[3][1] * temp.y + m[3][2] * temp.z + m[3][3] * temp.w;
}

void multMatrix4Matrix4(float** a, float** b, float** r)
{

  float r00 = (a[0][0] * b[0][0]) +  a[0][1] * b[1][0] +  a[0][2] * b[2][0] + a[0][3] * b[3][0];
  float r01 = (a[0][0] * b[0][1]) +  a[0][1] * b[1][1] +  a[0][2] * b[2][1] + a[0][3] * b[3][1];
  float r02 = (a[0][0] * b[0][2]) +  a[0][1] * b[1][2] +  a[0][2] * b[2][2] + a[0][3] * b[3][2];
  float r03 = (a[0][0] * b[0][3]) +  a[0][1] * b[1][3] +  a[0][2] * b[2][3] + a[0][3] * b[3][3];

  float r10 = (a[1][0] * b[0][0]) +  a[1][1] * b[1][0] +  a[1][2] * b[2][0] + a[1][3] * b[3][0];
  float r11 = (a[1][0] * b[0][1]) +  a[1][1] * b[1][1] +  a[1][2] * b[2][1] + a[1][3] * b[3][1];
  float r12 = (a[1][0] * b[0][2]) +  a[1][1] * b[1][2] +  a[1][2] * b[2][2] + a[1][3] * b[3][2];
  float r13 = (a[1][0] * b[0][3]) +  a[1][1] * b[1][3] +  a[1][2] * b[2][3] + a[1][3] * b[3][3];

  float r20 = (a[2][0] * b[0][0]) +  a[2][1] * b[1][0] +  a[2][2] * b[2][0] + a[2][3] * b[3][0];
  float r21 = (a[2][0] * b[0][1]) +  a[2][1] * b[1][1] +  a[2][2] * b[2][1] + a[2][3] * b[3][1];
  float r22 = (a[2][0] * b[0][2]) +  a[2][1] * b[1][2] +  a[2][2] * b[2][2] + a[2][3] * b[3][2];
  float r23 = (a[2][0] * b[0][3]) +  a[2][1] * b[1][3] +  a[2][2] * b[2][3] + a[2][3] * b[3][3];

  float r30 = (a[3][0] * b[0][0]) +  a[3][1] * b[1][0] +  a[3][2] * b[2][0] + a[3][3] * b[3][0];
  float r31 = (a[3][0] * b[0][1]) +  a[3][1] * b[1][1] +  a[3][2] * b[2][1] + a[3][3] * b[3][1];
  float r32 = (a[3][0] * b[0][2]) +  a[3][1] * b[1][2] +  a[3][2] * b[2][2] + a[3][3] * b[3][2];
  float r33 = (a[3][0] * b[0][3]) +  a[3][1] * b[1][3] +  a[3][2] * b[2][3] + a[3][3] * b[3][3];

  r[0][0] = r00; r[0][1] = r01; r[0][2] = r02; r[0][3] = r03;
  r[1][0] = r10; r[1][1] = r11; r[1][2] = r12; r[1][3] = r13;
  r[2][0] = r20; r[2][1] = r21; r[2][2] = r22; r[2][3] = r23;
  r[3][0] = r30; r[3][1] = r31; r[3][2] = r32; r[3][3] = r33;

}

void matrixTranspose(float** m, float **t,int size)
{
  // printMatrix(m,size);
  for(int i = 0; i < size; i++)
    for(int j = 0; j < size; j++)
      t[i][j] = m[j][i];
}

float** getRotationMatrix(float angle_x, float angle_y, float angle_z){

	float **rotacion, **tempRot;
	float angle;
	rotacion = (float**)malloc(sizeof(float*)*4);
	for(int i = 0; i < 4; i++)
		rotacion[i] = (float*)malloc(sizeof(float)*4);

	tempRot = (float**)malloc(sizeof(float*)*4);
	for(int i = 0; i < 4; i++)
		tempRot[i] = (float*)malloc(sizeof(float)*4);

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			rotacion[i][j] = tempRot[i][j] = static_cast<float>(i == j);

	if(angle_x != 0.0)
	{
	  angle = PI*angle_x/180;
	  tempRot[1][1] = cos(angle);
	  tempRot[1][2] = -sin(angle);
	  tempRot[2][1] = sin(angle);
	  tempRot[2][2] = cos(angle);
	  multMatrix4Matrix4(tempRot, rotacion, rotacion);
	}

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		  tempRot[i][j] = static_cast<float>(i == j);

	if(angle_y != 0.0)
	{
	  angle = PI*angle_y/180;
	  tempRot[0][0] = cos(angle);
	  tempRot[0][2] = sin(angle);
	  tempRot[2][0] = -sin(angle);
	  tempRot[2][2] = cos(angle);
	  //printMatrix(rotacion,4);
	  //return (float**)rotacion;
	  multMatrix4Matrix4(tempRot, rotacion, rotacion);
	}

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			tempRot[i][j] = static_cast<float>(i == j);

	if(angle_z != 0.0)
	{
	  angle = PI*angle_z/180;
	  tempRot[0][0] = cos(angle);
	  tempRot[0][1] = -sin(angle);
	  tempRot[1][0] = sin(angle);
	  tempRot[1][1] = cos(angle);
	  //printMatrix(rotacion,4);
	  //return (float**)rotacion;
	  multMatrix4Matrix4(tempRot, rotacion, rotacion);
	}

	for(int i = 0; i < 4; i++)
		free(tempRot[i]);

	free(tempRot);
	return (float**)rotacion;
}

float** getTranslationMatrix(float tx, float ty, float tz){

	float values[4] = {tx, ty, tz, 1.0f};
	float **translation = (float**)malloc(4*sizeof(float*));
	int i, j;

	for(i = 0; i < 4; i++)
	{
		translation[i] = (float*)malloc(4*sizeof(float));
		for(j = 0; j < 4; j++)
		{
			if(j == 3)
				translation[i][j] = values[i];
			else
				translation[i][j] = static_cast<float>(i==j);
		}
	}

//	for(i = 0; i < 4; i++)
//	{
//		for(j = 0; j < 4; j++)
//			cout << translation[i][j] << "\t";
//		cout << endl;
//	}

	return translation;

}

float** getScalingMatrix(float sx, float sy, float sz){

	float values[4] = {sx, sy, sz, 1.0f};
	float **scaling = (float**)malloc(4*sizeof(float*));
	int i, j;

	for(i = 0; i < 4; i++)
	{
		scaling[i] = (float*)malloc(4*sizeof(float));
		for(j = 0; j < 4; j++)
			scaling[i][j] = (i==j)?values[i]:0.0f;
	}

	return scaling;
}

unsigned char* readTextureFromBMP(char* filename, int &sizeX, int &sizeY)
{
	int i;
	FILE* f = fopen(filename, "rb");

	if(f == NULL){
		sizeX = 512;
		sizeY = 512;
		return NULL;
	}
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];
	sizeX = width;
	sizeY = height;
	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for(i = 0; i < size; i += 3)
	{
	  unsigned char tmp = data[i];
	  data[i] = data[i+2];
	  data[i+2] = tmp;
	}

	return data;
}

unsigned char* readBumpMapFromBMP(char* filename, int &sizeX, int &sizeY)
{
	int i;
	FILE* f = fopen(filename, "rb");

	if(f == NULL){
		sizeX = 512;
		sizeY = 512;
		return NULL;
	}
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];
	sizeX = width;
	sizeY = height;
	/*********************
	 * Changing size for single channel
	 *********************/
	int size = width * height;
	unsigned char* data = new unsigned char[3*size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), 3*size, f); // read the rest of the data at once
	fclose(f);

	unsigned char *oneChannelData = new unsigned char[size];

	for(i = 0; i < size; i++)
		oneChannelData[i] = data[3*i+1];

	delete data;
	return oneChannelData;
}

void getTexturePixelToVector3D(int u, int v, Vector3D& component, unsigned char *textureBuffer, int sizeX, int sizeY)
{
	if (u < 0)
		u = sizeX - 1 - (-u) % sizeX;
	else
		u = u % sizeX;

	if (v < 0)
		v = sizeY - 1 - (-v) % sizeY;
	else
		v = v % sizeY;

	unsigned int ind = (v * sizeX + u)*3;

	component.x = textureBuffer[ind]/255.0f;
	component.y = textureBuffer[ind+1]/255.0f;
	component.z = textureBuffer[ind+2]/255.0f;
}

void getNormalFromBumpMap(int u, int v, Vector3D& component, unsigned char *bumpMap, int sizeX, int sizeY, const Vector3D surfNormal)
{
	if (u < 0)
		u = sizeX - 1 - (-u) % sizeX;
	else
		u = u % sizeX;

	if (v < 0)
		v = sizeY - 1 - (-v) % sizeY;
	else
		v = v % sizeY;

	//Apply convolution and find gradient vector

	char horizontalGradientMask[3][3] = {{-1, 0, 1},
										{-2, 0, 2},
										{-1, 0, 1}};

	char verticalGradientMask[3][3] = {{-1, -2, -1},
										{0, 0, 0},
										{1, 2, 1}};
	unsigned int i, j;
	unsigned int ind;
	int sumHorizontal = 0;
	int sumVertical = 0;

	for(i = -1; i < 2; i++)
	{
		for(j = -1; j < 2; j++)
		{
			if((u + i < 0 || v + j < 0) || (u +i >= sizeX || v+j >= sizeY))
				continue;

			ind = (v+j) * sizeX + u+i;
			sumHorizontal += horizontalGradientMask[j+1][i+1]*bumpMap[ind];
			sumVertical += verticalGradientMask[j+1][i+1]*bumpMap[ind];
		}
	}

	component.x = (sumHorizontal/(4.0f*255))/sqrt(2.0);
	component.y = (sumVertical/(4.0f*255))/sqrt(2.0);
	component.z = 0.0f;

	if(component.x != 0.0f || component.y != 0.0f || component.z != 0.0f)
		cout << component << endl;

	//Find normal rotation

	Vector3D planeProjection;
	float oppSideMag;
	float adySideMag;

	planeProjection = surfNormal;
	planeProjection.y = 0.0f;

	oppSideMag = planeProjection.getMagnitude();
	adySideMag = surfNormal.y;

	float angleY = atan2(oppSideMag, adySideMag)*180/PI;


	planeProjection = surfNormal;
	planeProjection.x = 0.0f;

	oppSideMag = planeProjection.getMagnitude();
	adySideMag = surfNormal.x;

	float angleX = atan2(oppSideMag, adySideMag)*180/PI;

	//rotate gradient vector
	float **rotationMatrix = getRotationMatrix(angleX, angleY, 0.0f);

	multMatrixVector3D(rotationMatrix, component, component);

	for(i = 0; i < 4; i++)
		free(rotationMatrix[i]);

	free(rotationMatrix);
	//Add both vectors and normalize

	component = (component + surfNormal).getNormal();
}

float round(float num, unsigned char decimals){
	unsigned int factor = (unsigned int)pow(10.0f, decimals);
  return floor(num*factor + 0.5)/factor;
}
