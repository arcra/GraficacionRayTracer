#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <cstdlib>
#include "Structures.h"
#include "Vector3D.h"
#include "RayTracer.h"
#include "Surfaces.h"
#include "puntos.h"

#define IMAGE_WIDTH 700
#define IMAGE_HEIGHT 700

using namespace std;
using namespace RayTracing;


RayTracer *rayTracer;
GtkWidget *window, *drawingArea;

void initScene();
gboolean on_darea_expose (GtkWidget *widget,GdkEventExpose *event,gpointer user_data);

void initWindow(int argc, char *argv[]);


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


	material matTable;
	matTable.diffuse.x = 0.63f;
	matTable.diffuse.y = 0.32f;
	matTable.diffuse.z = 0.18f;
	matTable.specular = lowVector3D;
	matTable.reflective = nullVector3D;
	matTable.shininess = 1.0f;

	material matfloor1;
	matfloor1.diffuse.x = 0.0f;
	matfloor1.diffuse.y = 0.0f;
	matfloor1.diffuse.z = 0.0f;
	Vector3D specularF1(1.0f,1.0f,1.0f);
	matfloor1.specular = specularF1;
	Vector3D reflectiveF1(0.2f,0.2f,0.2f);
//	matfloor1.reflective = reflectiveF1;
	matfloor1.reflective = nullVector3D;
	matfloor1.shininess = 0.3f;

	material matfloor2;
	matfloor2.diffuse.x = 1.0f;
	matfloor2.diffuse.y = 1.0f;
	matfloor2.diffuse.z = 1.0f;
	Vector3D specularF2(1.0f,1.0f,1.0f);
	matfloor2.specular = specularF1;
//	Vector3D reflectiveF2(0.5f,0.5f,0.5f);
	matfloor2.reflective = nullVector3D;
	matfloor2.shininess = 0.3f;


	material matLeft;
	matLeft.diffuse.x = 0.0f;
	matLeft.diffuse.y = 0.0f;
	matLeft.diffuse.z = 1.0f;
	matLeft.specular = nullVector3D;
	matLeft.reflective = nullVector3D;
	matLeft.shininess = 0.1f;



	material matBack;
	matBack.diffuse.x = 1.0f;
	matBack.diffuse.y = 1.0f;
	matBack.diffuse.z = 1.0f;
	matBack.specular = nullVector3D;
	matBack.reflective = fullVector3D;
	matBack.shininess = 0.02f;


	material matFront;
	matFront.diffuse.x = 0.0f;
	matFront.diffuse.y = 1.0f;
	matFront.diffuse.z = 0.0f;
	matFront.specular = nullVector3D;
	matFront.reflective = nullVector3D;
	matFront.shininess = 1.0f;



	material matRight;
	matRight.diffuse.x = 1.0f;
	matRight.diffuse.y = 0.0f;
	matRight.diffuse.z = 0.0f;
	matRight.specular = nullVector3D;
	matRight.reflective = nullVector3D;
	matRight.shininess = 0.1f;



	material matTop;
	matTop.diffuse.x = 0.4f;
	matTop.diffuse.y = 0.2f;
	matTop.diffuse.z = 0.3f;
	matTop.specular = nullVector3D;
	matTop.reflective = nullVector3D;
	matTop.shininess = 0.1f;

	material matSp1;
	matSp1.diffuse.x = 0.0f;
	matSp1.diffuse.y = 1.0f;
	matSp1.diffuse.z = 1.0f;
	matSp1.specular = nullVector3D;
	matSp1.reflective = medVector3D;
	matSp1.shininess = 0.5f;

	material matSp2;
	matSp2.diffuse.x = 0.6f;
	matSp2.diffuse.y = 0.6f;
	matSp2.diffuse.z = 0.6f;
	matSp2.specular = hiVector3D;
	matSp2.reflective = fullVector3D;
	matSp2.shininess = 0.08f;

	material matSp3;
	matSp3.diffuse.x = 1.0f;
	matSp3.diffuse.y = 1.0f;
	matSp3.diffuse.z = 1.0f;
	matSp3.specular = nullVector3D;
	matSp3.reflective = nullVector3D;
	matSp3.shininess = 0.0f;


	Vector3D v1bis( 80.0f, 0.0f, 80.0f);
	Vector3D v2bis( 80.0f, 0.0f,-80.0f);
	Vector3D v3bis(-80.0f, 0.0f,-80.0f);
	Vector3D v4bis(-80.0f, 0.0f, 80.0f);

	Vector3D v1( 40.0f, 0.0f, 40.0f);
	Vector3D v2( 40.0f, 0.0f,-40.0f);
	Vector3D v3(-40.0f, 0.0f,-40.0f);
	Vector3D v4(-40.0f, 0.0f, 40.0f);

	Vector3D v5(-40.0f, 80.0f, 40.0f);
	Vector3D v6( 40.0f, 80.0f, 40.0f);
	Vector3D v7( 40.0f, 80.0f,-40.0f);
	Vector3D v8(-40.0f, 80.0f,-40.0f);

	//getFloor(matfloor1, matfloor2, rayTracer->surfaces,-40,-40,40,40,10.0);

	TriangleFace *plane3 = new TriangleFace(v4,v3,v5,matLeft);
	TriangleFace *plane4 = new TriangleFace(v5,v3,v8,matLeft);

	TriangleFace *plane5 = new TriangleFace(v3,v2,v8,matBack);
	TriangleFace *plane6 = new TriangleFace(v2,v7,v8,matBack);

	TriangleFace *plane7 = new TriangleFace(v2,v1,v6,matRight);
	TriangleFace *plane8 = new TriangleFace(v2,v6,v7,matRight);

	TriangleFace *plane9 = new TriangleFace(v8,v7,v6,matTop);
	TriangleFace *plane10 = new TriangleFace(v8,v6,v5,matTop);

	TriangleFace *plane11 = new TriangleFace(v4,v5,v6,matFront, false);
	TriangleFace *plane12 = new TriangleFace(v4,v6,v1,matFront, false);

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


	rayTracer->addSurface(plane5);
	rayTracer->addSurface(plane6);
	rayTracer->addSurface(plane7);
	rayTracer->addSurface(plane8);
	rayTracer->addSurface(plane3);
	rayTracer->addSurface(plane4);
	rayTracer->addSurface(plane9);
	rayTracer->addSurface(plane10);
	rayTracer->addSurface(plane11);
	rayTracer->addSurface(plane12);
	rayTracer->addSurface(sphere1);
	rayTracer->addSurface(sphere2);
	rayTracer->addSurface(sphere3);

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
