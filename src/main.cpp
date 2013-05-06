#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkdrawable.h>
#include <glib/gtypes.h>
#include <iostream>
#include <cstdlib>
#include "Structures.h"
#include "Vector3D.h"
#include "RayTracer.h"
#include "Surfaces.h"
//#include "puntos.h"

#define IMAGE_WIDTH 700
#define IMAGE_HEIGHT 700

using namespace std;
using namespace RayTracing;


RayTracer *rayTracer;
GtkWidget *window, *drawingArea;

void initScene();
gboolean on_darea_expose (GtkWidget *widget,GdkEventExpose *event,gpointer user_data);

void initWindow(int argc, char *argv[]);

void addCube(float size, Material mat);


int main(int argc, char* argv[])
{
  initWindow(argc,argv);
  initScene();

  rayTracer->renderScence();

  gtk_main();

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


void initScene()
{
	rayTracer = new RayTracer(IMAGE_WIDTH, IMAGE_HEIGHT);

	Vector3D pos(0.0f, 40.0f, 190.0f);
	Vector3D u(0.0f, 1.0f, 0.0f);
	Vector3D dir(0.0f, 40.0f, 0.0f);

	rayTracer->camera = new Camera(pos,u,dir,true);
	rayTracer->camera->setView(60.0f,20.0f,-20.0f,20.0f);
	rayTracer->camera->focalPoint = 110.0f;

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
	matFloor.diffuse.z = 0.8f;
	//matFloor.specular = Vector3D(1.0f,1.0f,1.0f);
	matFloor.specular = nullVector3D;
	matFloor.reflective = nullVector3D;
	matFloor.shininess = 0.3f;
	matFloor.textureMap = readTextureFromBMP("resources/floor_texture.bmp", matFloor.sizeMapX, matFloor.sizeMapY);
	matFloor.bumpMap = readBumpMapFromBMP("resources/floor_bump.bmp", matFloor.sizeMapX, matFloor.sizeMapY);

	Material matLeft;
	matLeft.diffuse.x = 0.0f;
	matLeft.diffuse.y = 0.0f;
	matLeft.diffuse.z = 1.0f;
	matLeft.specular = nullVector3D;
	matLeft.reflective = nullVector3D;
	matLeft.shininess = 0.1f;

	Material matBack;
	matBack.diffuse.x = 1.0f;
	matBack.diffuse.y = 1.0f;
	matBack.diffuse.z = 1.0f;
	matBack.specular = nullVector3D;
	matBack.reflective = nullVector3D;
	matBack.shininess = 0.02f;

	Material matFront;
	matFront.diffuse.x = 0.0f;
	matFront.diffuse.y = 1.0f;
	matFront.diffuse.z = 0.0f;
	matFront.specular = nullVector3D;
	matFront.reflective = nullVector3D;
	matFront.shininess = 1.0f;

	Material matRight;
	matRight.diffuse.x = 1.0f;
	matRight.diffuse.y = 0.0f;
	matRight.diffuse.z = 0.0f;
	matRight.specular = nullVector3D;
	matRight.reflective = nullVector3D;
	matRight.shininess = 0.1f;

	Material matTop;
	matTop.diffuse.x = 0.4f;
	matTop.diffuse.y = 0.2f;
	matTop.diffuse.z = 0.3f;
	matTop.specular = nullVector3D;
	matTop.reflective = nullVector3D;
	matTop.shininess = 0.1f;

	Material matSp1;
	matSp1.diffuse.x = 1.0f;
	matSp1.diffuse.y = 0.85f;
	matSp1.diffuse.z = 0.0f;
	matSp1.specular = fullVector3D;
	matSp1.reflective = medVector3D;
	matSp1.shininess = 25.0f;

	Material matSp2;
//	matSp2.diffuse.x = 0.6f;
//	matSp2.diffuse.y = 0.6f;
//	matSp2.diffuse.z = 0.6f;
	matSp2.diffuse.x = 1.0f;
	matSp2.diffuse.y = 1.0f;
	matSp2.diffuse.z = 1.0f;
	matSp2.specular = medVector3D;
//	matSp2.reflective = fullVector3D;
	matSp2.reflective = nullVector3D;
	matSp2.shininess = 25.0f;
	matSp2.textureMap = readTextureFromBMP("resources/worldMap_texture.bmp", matSp2.sizeMapX, matSp2.sizeMapY);
	matSp2.bumpMap = readBumpMapFromBMP("resources/worldMap_bump.bmp", matSp2.sizeMapX, matSp2.sizeMapY);

	Material matSp3;
	matSp3.diffuse.x = 1.0f;
	matSp3.diffuse.y = 1.0f;
	matSp3.diffuse.z = 1.0f;
	matSp3.specular = nullVector3D;
	matSp3.reflective = nullVector3D;
	matSp3.shininess = 1.0f;


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

	TriangleFace *plane1 = new TriangleFace(Vertex(v2, 1.0f, 0.0f), Vertex(v3, 0.0f, 0.0f), Vertex(v4, 0.0f, 1.0f), matFloor);
	TriangleFace *plane2 = new TriangleFace(Vertex(v2, 1.0f, 0.0f), Vertex(v4, 0.0f, 1.0f), Vertex(v1, 1.0f, 1.0f), matFloor);

	TriangleFace *plane3 = new TriangleFace(Vertex(v4), Vertex(v3), Vertex(v8), matLeft);
	TriangleFace *plane4 = new TriangleFace(Vertex(v5), Vertex(v4), Vertex(v8), matLeft);

	TriangleFace *plane5 = new TriangleFace(Vertex(v3), Vertex(v7), Vertex(v8), matBack);
	TriangleFace *plane6 = new TriangleFace(Vertex(v2), Vertex(v7), Vertex(v3), matBack);

	TriangleFace *plane7 = new TriangleFace(Vertex(v7), Vertex(v2), Vertex(v6), matRight);
	TriangleFace *plane8 = new TriangleFace(Vertex(v6), Vertex(v2), Vertex(v1), matRight);

	TriangleFace *plane9 = new TriangleFace(Vertex(v8), Vertex(v7), Vertex(v6), matTop);
	TriangleFace *plane10 = new TriangleFace(Vertex(v8), Vertex(v6), Vertex(v5), matTop);

	TriangleFace *plane11 = new TriangleFace(Vertex(v5), Vertex(v6), Vertex(v1), matFront);
	TriangleFace *plane12 = new TriangleFace(Vertex(v5), Vertex(v1), Vertex(v4), matFront);

	float offsetX1,offsetX2,
	    offsetY1,offsetY2,
	    offsetZ1,offsetZ2,radio;

	radio = 8.0f;

	Vector3D centroMesa1(10.5f,21.0f,21.0f);
	Vector3D centroMesa2(10.5f,21.0f,21.0f);

	offsetX1 = 10.0f;
	offsetY1 = -5.0f;
	offsetZ1 = 10.0f;
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

	rayTracer->pushMatrix();

		rayTracer->scale(15.0, 2.0, 25.0);
		rayTracer->rotate(0.0f, 40.0f, 0.0f);
		rayTracer->translate(-10.0, 15.0, 5.0);

		addCube(1.0f, matTable);

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
	rayTracer->addSurface(sphere2);
	rayTracer->addSurface(sphere3);


}

void addCube(float size, Material mat)
{
	float halfSize = size/2.0f;
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

	Vector3D v1( halfSize, -halfSize, halfSize);
	Vector3D v2( halfSize, -halfSize,-halfSize);
	Vector3D v3(-halfSize, -halfSize,-halfSize);
	Vector3D v4(-halfSize, -halfSize, halfSize);

	Vector3D v5(-halfSize, halfSize, halfSize);
	Vector3D v6( halfSize, halfSize, halfSize);
	Vector3D v7( halfSize, halfSize,-halfSize);
	Vector3D v8(-halfSize, halfSize,-halfSize);

	rayTracer->addSurface(new TriangleFace(v1,v3,v2,mat));
	rayTracer->addSurface(new TriangleFace(v1,v4,v3,mat));

	rayTracer->addSurface(new TriangleFace(v5,v3,v4,mat));
	rayTracer->addSurface(new TriangleFace(v8,v3,v5,mat));

	rayTracer->addSurface(new TriangleFace(v8,v2,v3,mat));
	rayTracer->addSurface(new TriangleFace(v8,v7,v2,mat));

	rayTracer->addSurface(new TriangleFace(v6,v1,v7,mat));
	rayTracer->addSurface(new TriangleFace(v7,v1,v2,mat));

	rayTracer->addSurface(new TriangleFace(v5,v7,v8,mat));
	rayTracer->addSurface(new TriangleFace(v5,v6,v7,mat));

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
