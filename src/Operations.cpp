
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

unsigned char* readBMP(char* filename, int &sizeX, int &sizeY)
{
  //cout << filename << endl;
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

  //cout << filename << endl;
  return data;
}

void getTexturePixelToVector3D(int i, int j, Vector3D& component, unsigned char *textureBuffer, int sizeX, int sizeY)
{
  if (i < 0)
    i = sizeX - 1 - (-i) % sizeX;
  else
    i = i % sizeX;

  if (j < 0)
    j = sizeY - 1 - (-j) % sizeY;
  else
    j = j % sizeY;

  unsigned int ind = (j * sizeX + i)*3;

  component.x = textureBuffer[ind]/255.0f;
  component.y = textureBuffer[ind+1]/255.0f;
  component.z = textureBuffer[ind+2]/255.0f;
  //  cout << rgb[0]*1 << " " << rgb[1]*1 << " " << rgb[2]*1 <<endl;
}

float round(float num, unsigned char decimals){
	unsigned int factor = (unsigned int)pow(10.0f, decimals);
  return floor(num*factor + 0.5)/factor;
}
