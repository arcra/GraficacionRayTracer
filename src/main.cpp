#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkdrawable.h>
#include <glib/gtypes.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Structures.h"
#include "Vector3D.h"
#include "RayTracer.h"
#include "Surfaces.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
//#include <stringstream>
#include <sstream>


#define IMAGE_WIDTH 700
#define IMAGE_HEIGHT 700

#define PI (3.141592653589793)

using namespace std;
using namespace RayTracing;


RayTracer *rayTracer;
GtkWidget *window, *drawingArea;

void initScene(float pf);
gboolean on_darea_expose (GtkWidget *widget,GdkEventExpose *event,gpointer user_data);

void initWindow(int argc, char *argv[]);

void addCube(float size, Material mat);
void addTable(float x, float y , float z, Material matTable);
void addMirror(Material mat);

int main(int argc, char* argv[])
{
  initWindow(argc,argv);
  
  if(argc < 2)
    initScene(110.0);
  else
    {
      float pf = atof(argv[1]);
      initScene(pf);
    }
	
  rayTracer->renderScence();

  // gtk_main();
  
  
  if(argc > 1	)
    {
      stringstream ss;
      int ind = atoi(argv[2]);
      //string ruta("./im"); 
      ss << "./imagenes/im";
      ind = 81 + ind;
      //string as(ind);
      ss << ind;	
      //ruta += as;
      //ruta += ".ppm";
      ss << ".ppm";
      FILE *out;
      out = fopen(ss.str().c_str(),"wb");
      fprintf(out,"P6\n%d %d\n255\n",IMAGE_WIDTH,IMAGE_HEIGHT);
      fwrite(rayTracer->getImageBuffer(),1,IMAGE_WIDTH*IMAGE_HEIGHT*3,out);
      fclose(out);
    }

  delete rayTracer;
  //  free(window);
  //  free(drawingArea);
  return 0;
}

gboolean on_darea_expose (GtkWidget *widget,
			  GdkEventExpose *event,
			  gpointer user_data)
{
  gdk_draw_rgb_image (widget->window,
		      widget->style->fg_gc[GTK_STATE_NORMAL],
		      0, 0, IMAGE_WIDTH, IMAGE_HEIGHT,
		      GDK_RGB_DITHER_MAX, rayTracer->getImageBuffer(), IMAGE_WIDTH * 3);
  return true;
}


void initScene(float pf)
{

  rayTracer = new RayTracer(IMAGE_WIDTH, IMAGE_HEIGHT);

  /*Vector3D pos(0.0f, 40.0f, 190.0f);
    Vector3D u(0.0f, 1.0f, 0.0f);
    //Doesn't matter, since rays are defined by viewport position
    Vector3D dir(0.0f, 40.0f, 0.0f);

    rayTracer->camera = new Camera(pos,u,dir,true);
    rayTracer->camera->setView(60.0f,20.0f,-20.0f,20.0f);
    rayTracer->camera->focalPoint = 110.0f;*/
	
  //float posCamaraX = 80.0f, posCamaraY = 40.0f, posCamaraZ = 0.0f;
  float posCamaraX = 0.0f, posCamaraY = 40.0f, posCamaraZ = 80.0f;
	
  float pFocal = pf;
  Vector3D pos(posCamaraX, posCamaraY, posCamaraZ+pFocal);
  Vector3D u(0.0f, 1.0f, 0.0f);
  //Doesn't matter, since rays are defined by viewport position
  Vector3D dir(0.0f, 40.0f, 0.0f);

  rayTracer->camera = new Camera(pos,u,dir,true);
  rayTracer->camera->setView(60.0f,20.0f,-20.0f,20.0f);
  rayTracer->camera->focalPoint = pFocal;
	
  rayTracer->addLight(0.0f, 70.0f, 0.0f, 1.0f, 1.0f, 1.0f);

  //	rayTracer->addLight(30.0f, 40.0f, -10.0f, 0.7f, 0.7f, 1.0f);

  Vector3D nullVector3D(0.0f, 0.0f, 0.0f);
  Vector3D lowVector3D(0.2f, 0.2f, 0.2f);
  Vector3D medVector3D(0.5f, 0.5f, 0.5f);
  Vector3D hiVector3D(0.9f, 0.9f, 0.9f);
  Vector3D fullVector3D(1.0f, 1.0f, 1.0f);


  Material matTable;
  matTable.diffuse.x = 0.63f;
  matTable.diffuse.y = 0.32f;
  matTable.diffuse.z = 0.18f;
  matTable.specular = lowVector3D;
  matTable.reflective = nullVector3D;
  matTable.shininess = 1.0f;

  Material matFloor;
  matFloor.diffuse.x = 0.8f;
  matFloor.diffuse.y = 0.8f;
  matFloor.diffuse.z = 1.0f;
  //matFloor.specular = Vector3D(1.0f,1.0f,1.0f);
  matFloor.specular = nullVector3D;
  matFloor.reflective = nullVector3D;
  matFloor.shininess = 0.3f;
  matFloor.textureMap = readTextureFromBMP("resources/floor_texture.bmp", matFloor.sizeMapX, matFloor.sizeMapY);
  matFloor.bumpMap = readBumpMapFromBMP("resources/floor_texture_jigsaw_bump.bmp", matFloor.sizeMapX, matFloor.sizeMapY);

  Material matTableBump;
  matTableBump.diffuse.x = 0.63f;
  matTableBump.diffuse.y = 0.32f;
  matTableBump.diffuse.z = 0.18f;
  matTableBump.specular = lowVector3D;
  matTableBump.reflective = nullVector3D;
  matTableBump.shininess = 1.0f;
  matTableBump.textureMap = readTextureFromBMP("resources/wood_texture2.bmp", matTableBump.sizeMapX, matTableBump.sizeMapY);
  matTableBump.bumpMap = readBumpMapFromBMP("resources/wood_bump2.bmp", matTableBump.sizeMapX, matTableBump.sizeMapY);

  Material matLeft;
  matLeft.diffuse.x = 0.0f;
  matLeft.diffuse.y = 0.0f;
  matLeft.diffuse.z = 1.0f;
  matLeft.specular = nullVector3D;
  matLeft.reflective = nullVector3D;
  matLeft.shininess = 0.1f;
  matLeft.textureMap = readTextureFromBMP("resources/pared.bmp", matLeft.sizeMapX, matLeft.sizeMapY);
  matLeft.bumpMap = readBumpMapFromBMP("resources/pared_bump.bmp", matLeft.sizeMapX, matLeft.sizeMapY);

  Material matBack;
  matBack.diffuse.x = 1.0f;
  matBack.diffuse.y = 1.0f;
  matBack.diffuse.z = 1.0f;
  matBack.specular = nullVector3D;
  matBack.reflective = nullVector3D;
  matBack.shininess = 0.02f;
  matBack.textureMap = readTextureFromBMP("resources/pared.bmp", matBack.sizeMapX, matBack.sizeMapY);
  matBack.bumpMap = readBumpMapFromBMP("resources/pared_bump.bmp", matBack.sizeMapX, matBack.sizeMapY);

  Material matFront;
  matFront.diffuse.x = 0.0f;
  matFront.diffuse.y = 1.0f;
  matFront.diffuse.z = 0.0f;
  matFront.specular = nullVector3D;
  matFront.reflective = nullVector3D;
  matFront.shininess = 1.0f;
  matFront.textureMap = readTextureFromBMP("resources/renassain.bmp", matFront.sizeMapX, matFront.sizeMapY);
  //matFront.bumpMap = readBumpMapFromBMP("resources/pared_bump_front.bmp", matFront.sizeMapX, matFront.sizeMapY);

  Material matRight;
  matRight.diffuse.x = 1.0f;
  matRight.diffuse.y = 0.0f;
  matRight.diffuse.z = 0.0f;
  matRight.specular = nullVector3D;
  matRight.reflective = nullVector3D;
  matRight.shininess = 0.1f;
  matRight.textureMap = readTextureFromBMP("resources/pared.bmp", matRight.sizeMapX, matRight.sizeMapY);
  matRight.bumpMap = readBumpMapFromBMP("resources/pared_bump.bmp", matRight.sizeMapX, matRight.sizeMapY);

  Material matTop;
  matTop.diffuse.x = 0.4f;
  matTop.diffuse.y = 0.2f;
  matTop.diffuse.z = 0.3f;
  matTop.specular = nullVector3D;
  matTop.reflective = nullVector3D;
  matTop.shininess = 0.1f;
  matTop.textureMap = readTextureFromBMP("resources/sixtina.bmp", matTop.sizeMapX, matTop.sizeMapY);
  //matTop.bumpMap = readBumpMapFromBMP("resources/pared_bump.bmp", matRight.sizeMapX, matRight.sizeMapY);
	
	

  Material matSp1;
  matSp1.diffuse.x = 0.86f;
  matSp1.diffuse.y = 0.75f;
  matSp1.diffuse.z = 0.1f;
  matSp1.specular = fullVector3D;
  matSp1.reflective = lowVector3D;
  matSp1.shininess = 25.0f;

  Material matSp2;
  matSp2.diffuse.x = 0.6f;
  matSp2.diffuse.y = 0.6f;
  matSp2.diffuse.z = 0.9f;
  matSp2.specular = fullVector3D;
  matSp2.reflective = hiVector3D;
  //	matSp2.reflective = nullVector3D;
  matSp2.shininess = 25.0f;
  //	matSp2.textureMap = readTextureFromBMP("resources/WorldMapReal_texture.bmp", matSp2.sizeMapX, matSp2.sizeMapY);
  //	matSp2.bumpMap = readBumpMapFromBMP("resources/WorldMapReal_bump.bmp", matSp2.sizeMapX, matSp2.sizeMapY);

  Material matSp3;
  matSp3.diffuse.x = 1.0f;
  matSp3.diffuse.y = 1.0f;
  matSp3.diffuse.z = 1.0f;
  matSp3.specular = fullVector3D;
  matSp3.reflective = nullVector3D;
  matSp3.shininess = 30.0f;

  Material matMirror;
  matMirror.diffuse.x = 0.9f;
  matMirror.diffuse.y = 0.9f;
  matMirror.diffuse.z = 1.0f;
  matMirror.specular = hiVector3D;
  matMirror.reflective = fullVector3D;
  matMirror.shininess = 25.0f;


  Vector3D v1bis( 80.0f, 0.0f, 80.0f);
  Vector3D v2bis( 80.0f, 0.0f,-80.0f);
  Vector3D v3bis(-80.0f, 0.0f,-80.0f);
  Vector3D v4bis(-80.0f, 0.0f, 80.0f);


  /*
    8------------7
    /|           /|
    / |          / |
    5------------6  |
    |  3---------|--2
    | /          | /
    |/           |/
    4----------- 1
  */


  Vector3D v1( 40.0f, 0.0f, 40.0f);
  Vector3D v2( 40.0f, 0.0f,-40.0f);
  Vector3D v3(-40.0f, 0.0f,-40.0f);
  Vector3D v4(-40.0f, 0.0f, 40.0f);

  Vector3D v5(-40.0f, 80.0f, 40.0f);
  Vector3D v6( 40.0f, 80.0f, 40.0f);
  Vector3D v7( 40.0f, 80.0f,-40.0f);
  Vector3D v8(-40.0f, 80.0f,-40.0f);

  TriangleFace *plane1 = new TriangleFace(Vertex(v2, 1.0f, 1.0f), Vertex(v3, 0.0f, 1.0f), Vertex(v4, 0.0f, 0.0f), matFloor);
  TriangleFace *plane2 = new TriangleFace(Vertex(v2, 1.0f, 1.0f), Vertex(v4, 0.0f, 0.0f), Vertex(v1, 1.0f, 0.0f), matFloor);

  TriangleFace *plane3 = new TriangleFace(Vertex(v4, 0.0f, 0.0f), Vertex(v3, 1.0f, 0.0f), Vertex(v8, 1.0f, 1.0f), matLeft);
  TriangleFace *plane4 = new TriangleFace(Vertex(v5, 0.0f, 1.0f), Vertex(v4, 0.0f, 0.0f), Vertex(v8, 1.0f, 1.0f), matLeft);


  /*
    8------------7
    /|           /|
    / |          / |
    5------------6  |
    |  3---------|--2
    | /          | /
    |/           |/
    4----------- 1
  */
	

  TriangleFace *plane5 = new TriangleFace(Vertex(v3,0.0f,0.0f), Vertex(v7,1.0f,1.0f), Vertex(v8,0.0f,1.0f), matBack);
  TriangleFace *plane6 = new TriangleFace(Vertex(v2,1.0f,0.0f), Vertex(v7,1.0f,1.0f), Vertex(v3,0.0f,0.0f), matBack);

  TriangleFace *plane7 = new TriangleFace(Vertex(v7,0.0f,1.0f), Vertex(v2,0.0f,0.0f), Vertex(v6,1.0f,1.0f), matRight);
  TriangleFace *plane8 = new TriangleFace(Vertex(v6,1.0f,1.0f), Vertex(v2,0.0f,0.0f), Vertex(v1,1.0f,0.0f), matRight);

  TriangleFace *plane9 = new TriangleFace(Vertex(v8, 0.0f, 0.0f), Vertex(v7, 1.0f, 0.0f), Vertex(v6, 1.0f, 1.0f), matTop);
  TriangleFace *plane10 = new TriangleFace(Vertex(v8, 0.0f, 0.0f), Vertex(v6, 1.0f, 1.0f), Vertex(v5, 0.0f, 1.0f), matTop);

  TriangleFace *plane11 = new TriangleFace(Vertex(v5, 1.0f, 1.0f), Vertex(v6, 0.0f, 1.0f), Vertex(v1, 0.0f, 0.0f), matFront);
  TriangleFace *plane12 = new TriangleFace(Vertex(v5, 1.0f, 1.0f), Vertex(v1, 0.0f, 0.0f), Vertex(v4, 1.0f, 0.0f), matFront);

  float offsetX1,offsetX2,
    offsetY1,offsetY2,
    offsetZ1,offsetZ2,radio;

  radio = 8.0f;

  Vector3D centroMesa1(10.5f,21.0f,21.0f);
  Vector3D centroMesa2(10.5f,21.0f,21.0f);

  offsetX1 = 0.0f;
  offsetY1 = -5.0f;
  offsetZ1 = 0.0f;
  Vector3D offsetM1(offsetX1,offsetY1,offsetZ1);
  offsetX2 = -30.0f;
  offsetY2 = -5.0f;
  offsetZ2 = -30.0f;
  Vector3D offsetM2(offsetX2,offsetY2,offsetZ2);

  Vector3D sphpos1(0.0f,radio,0.0f);
  Vector3D sphpos2(0.0f,radio,0.0f);
  Vector3D sphpos3(0.0f,79.0f,0.0f);

  Sphere *sphere1 = new Sphere(radio,sphpos1+offsetM1+centroMesa1,matSp1);
  Sphere *sphere2 = new Sphere(radio,sphpos2+offsetM2+centroMesa2,matSp2);
  Sphere *sphere3 = new Sphere(0.5f,sphpos3,matSp3);

  addTable(-20,0,-10,matTableBump);
  addTable(20,0,25,matTableBump);
	
  rayTracer->pushMatrix();
  rayTracer->translate(1.0,40.0,-39.7);
  rayTracer->scale(60.0,30.0,1.0);
  addMirror(matMirror);
  rayTracer->popMatrix();
		
  rayTracer->pushMatrix();
  rayTracer->translate(1.0,40.0,-39.9);
  rayTracer->scale(63.0,33.0,1.0);
  addMirror(matTable);
  rayTracer->popMatrix();

  rayTracer->addSurface(plane1);
  rayTracer->addSurface(plane2);
  rayTracer->addSurface(plane3);
  rayTracer->addSurface(plane4);
  rayTracer->addSurface(plane5);
  rayTracer->addSurface(plane6);
  rayTracer->addSurface(plane7);
  rayTracer->addSurface(plane8);
  rayTracer->addSurface(plane9);
  rayTracer->addSurface(plane10);
  rayTracer->addSurface(plane11);
  rayTracer->addSurface(plane12);
  rayTracer->addSurface(sphere1);

  rayTracer->pushMatrix();
  //rayTracer->rotate(0.0f, 0.0f, 0.0f);
  rayTracer->addSurface(sphere2);
  rayTracer->popMatrix();

  rayTracer->addSurface(sphere3);


}

void addCube(float size, Material mat)
{
  float halfSize = size/2.0f;

  Vector3D v1( halfSize, -halfSize, halfSize);
  Vector3D v2( halfSize, -halfSize,-halfSize);
  Vector3D v3(-halfSize, -halfSize,-halfSize);
  Vector3D v4(-halfSize, -halfSize, halfSize);

  Vector3D v5(-halfSize, halfSize, halfSize);
  Vector3D v6( halfSize, halfSize, halfSize);
  Vector3D v7( halfSize, halfSize,-halfSize);
  Vector3D v8(-halfSize, halfSize,-halfSize);

  /*	 8------------7
	 /|           /|
	 / |          / |
	 5------------6  |
	 |  3---------|--2
	 | /          | /
	 |/           |/
	 4----------- 1 */
	
  rayTracer->addSurface(new TriangleFace(Vertex(v1,1.0f,1.0f),Vertex(v3,0.0f,0.0f),Vertex(v2,1.0f,0.0f),mat));
  rayTracer->addSurface(new TriangleFace(Vertex(v1,1.0f,1.0f),Vertex(v4,0.0f,0.0f),Vertex(v3,0.0f,0.0f),mat));

  rayTracer->addSurface(new TriangleFace(Vertex(v5,1.0f,1.0f),Vertex(v3,0.0f,0.0f),Vertex(v4,1.0f,0.0f),mat));
  rayTracer->addSurface(new TriangleFace(Vertex(v8,0.0f,1.0f),Vertex(v3,0.0f,0.0f),Vertex(v5,1.0f,1.0f),mat));

  rayTracer->addSurface(new TriangleFace(Vertex(v8,1.0f,1.0f),Vertex(v2,0.0f,0.0f),Vertex(v3,1.0f,0.0f),mat));
  rayTracer->addSurface(new TriangleFace(Vertex(v8,1.0f,1.0f),Vertex(v7,0.0f,1.0f),Vertex(v2,0.0f,0.0f),mat));

  rayTracer->addSurface(new TriangleFace(Vertex(v6,0.0f,1.0f),Vertex(v1,0.0f,0.0f),Vertex(v7,1.0f,1.0f),mat));
  rayTracer->addSurface(new TriangleFace(Vertex(v7,1.0f,1.0f),Vertex(v1,0.0f,0.0f),Vertex(v2,1.0f,0.0f),mat));

  rayTracer->addSurface(new TriangleFace(Vertex(v5,0.0f,0.0f),Vertex(v7,1.0f,1.0f),Vertex(v8,0.0f,1.0f),mat));
  rayTracer->addSurface(new TriangleFace(Vertex(v5,0.0f,0.0f),Vertex(v6,1.0f,0.0f),Vertex(v7,1.0f,1.0f),mat));

  rayTracer->addSurface(new TriangleFace(Vertex(v6,1.0f,1.0f),Vertex(v5,0.0f,1.0f),Vertex(v4,0.0f,0.0f),mat));
  rayTracer->addSurface(new TriangleFace(Vertex(v1,1.0f,0.0f),Vertex(v6,1.0f,1.0f),Vertex(v4,0.0f,0.0f),mat));
}


void addTable(float x, float y , float z, Material matTable)
{

	rayTracer->pushMatrix();
		rayTracer->translate(x,y,z);

		rayTracer->pushMatrix();
			rayTracer->translate(0.0, 15.0, 0.0);
			//rayTracer->rotate(0.0f, 40.0f, 0.0f);
			rayTracer->scale(15.0, 2.0, 25.0);
			addCube(1.0f, matTable);
		rayTracer->popMatrix();

	 
		rayTracer->pushMatrix();
			rayTracer->translate(6.5, 7.0, 11.5);
			//rayTracer->rotate(0.0f, 40.0f, 0.0f);
			rayTracer->scale(2.0,14.0,2.0);
			addCube(1.0f, matTable);
		rayTracer->popMatrix();
	 
		rayTracer->pushMatrix();
			rayTracer->translate(-6.5, 7.0, 11.5);
			//rayTracer->rotate(0.0f, 40.0f, 0.0f);
			rayTracer->scale(2.0,14.0,2.0);
			addCube(1.0f, matTable);
		rayTracer->popMatrix();
	 
		rayTracer->pushMatrix();
			rayTracer->translate(-6.5, 7.0, -11.5);
			//rayTracer->rotate(0.0f, 40.0f, 0.0f);
			rayTracer->scale(2.0,14.0,2.0);
			addCube(1.0f, matTable);
		rayTracer->popMatrix();
	 
		rayTracer->pushMatrix();
			rayTracer->translate(6.5, 7.0, -11.5);
			//rayTracer->rotate(0.0f, 40.0f, 0.0f);
			rayTracer->scale(2.0,14.0,2.0);
			addCube(1.0f, matTable);
		rayTracer->popMatrix();


  rayTracer->popMatrix();
}

void addMirror(Material mat)
{
  float halfSize = 1.0/2.0f;
	
  Vector3D v1( halfSize, -halfSize, halfSize);
  Vector3D v2( halfSize, -halfSize,-halfSize);
  Vector3D v3(-halfSize, -halfSize,-halfSize);
  Vector3D v4(-halfSize, -halfSize, halfSize);

  Vector3D v5(-halfSize, halfSize, halfSize);
  Vector3D v6( halfSize, halfSize, halfSize);
  Vector3D v7( halfSize, halfSize,-halfSize);
  Vector3D v8(-halfSize, halfSize,-halfSize);
	
  rayTracer->addSurface(new TriangleFace(v6,v5,v4,mat));
  rayTracer->addSurface(new TriangleFace(v1,v6,v4,mat));
	
}


void initWindow(int argc, char *argv[]){

  //cout << IMAGE_WIDTH << " " << IMAGE_HEIGHT << " " << 3 << endl;

  gtk_init (&argc, &argv);
  gdk_rgb_init();
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  drawingArea = gtk_drawing_area_new();
  gtk_drawing_area_size (GTK_DRAWING_AREA (drawingArea), IMAGE_WIDTH,
			 IMAGE_HEIGHT);
  gtk_container_add (GTK_CONTAINER (window), drawingArea);
  gtk_signal_connect (GTK_OBJECT (drawingArea), "expose-event",
		      GTK_SIGNAL_FUNC (on_darea_expose), NULL);
  g_signal_connect(G_OBJECT(window), "destroy",
		   G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all (window);
}
