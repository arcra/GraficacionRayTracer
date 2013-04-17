#include <gtk/gtk.h>
#include <glib.h>
#include <iostream>
#include <cstdlib>
#include "xcStructures.h"
#include "xcarVector.h"
#include "xcarjiRayTracer.h"
#include "xcarjiSurfaces.h"
#include "puntos.h"

#define IMAGE_WIDTH 700
#define IMAGE_HEIGHT 700

using namespace std;
using namespace xcarjiRayTracing;


xcarjiRayTracer *rayTracer;
guchar* rgbbuf;
/*sphere mySphere, mySphere2, mySphere3;
  xcarTrianglePlane plano1,plano2;*/
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
		      GDK_RGB_DITHER_MAX, rgbbuf, IMAGE_WIDTH * 3);
  return true;
}


void initRGBbuffer()
{

  rgbbuf = (guchar*)malloc(sizeof(guchar)*IMAGE_WIDTH * IMAGE_HEIGHT * 3);
  gint x, y;
  guchar *pos;
  pos = rgbbuf;
  for (y = 0; y < IMAGE_HEIGHT; y++)
    {
      for (x = 0; x < IMAGE_WIDTH; x++)
	{
	  *pos++ = 0;
	  *pos++ = 0;
	  *pos++ = 0;
	}
    }
}

void initScene()
{
	initRGBbuffer();
	rayTracer = new xcarjiRayTracer(IMAGE_WIDTH, IMAGE_HEIGHT, rgbbuf);

	xcarVector pos(0.0f, 40.0f, 190.0f);
	xcarVector u(0.0f, 1.0f, 0.0f);
	xcarVector dir(0.0f, 40.0f, 0.0f);

	rayTracer->camera = new xcCamera(pos,u,dir,true);
	rayTracer->camera->setView(60.0f,20.0f,-20.0f,20.0f);
	rayTracer->camera->focalPoint = 110.0f;

	rayTracer->addLight(0.0f, 70.0f, 0.0f, 1.0f, 1.0f, 1.0f);

//	rayTracer->addLight(30.0f, 40.0f, -10.0f, 0.7f, 0.7f, 1.0f);

	xcarVector nullVector(0.0f, 0.0f, 0.0f);
	xcarVector lowVector(0.2f, 0.2f, 0.2f);
	xcarVector medVector(0.5f, 0.5f, 0.5f);
	xcarVector hiVector(0.9f, 0.9f, 0.9f);
	xcarVector fullVector(1.0f, 1.0f, 1.0f);


	material matTable;
	matTable.diffuse.x = 0.63f;
	matTable.diffuse.y = 0.32f;
	matTable.diffuse.z = 0.18f;
	matTable.specular = lowVector;
	matTable.reflective = nullVector;
	matTable.shininess = 1.0f;

	material matfloor1;
	matfloor1.diffuse.x = 0.0f;
	matfloor1.diffuse.y = 0.0f;
	matfloor1.diffuse.z = 0.0f;
	xcarVector specularF1(1.0f,1.0f,1.0f);
	matfloor1.specular = specularF1;
	xcarVector reflectiveF1(0.2f,0.2f,0.2f);
//	matfloor1.reflective = reflectiveF1;
	matfloor1.reflective = nullVector;
	matfloor1.shininess = 0.3f;

	material matfloor2;
	matfloor2.diffuse.x = 1.0f;
	matfloor2.diffuse.y = 1.0f;
	matfloor2.diffuse.z = 1.0f;
	xcarVector specularF2(1.0f,1.0f,1.0f);
	matfloor2.specular = specularF1;
//	xcarVector reflectiveF2(0.5f,0.5f,0.5f);
	matfloor2.reflective = nullVector;
	matfloor2.shininess = 0.3f;


	material matLeft;
	matLeft.diffuse.x = 0.0f;
	matLeft.diffuse.y = 0.0f;
	matLeft.diffuse.z = 1.0f;
	matLeft.specular = nullVector;
	matLeft.reflective = nullVector;
	matLeft.shininess = 0.1f;



	material matBack;
	matBack.diffuse.x = 1.0f;
	matBack.diffuse.y = 1.0f;
	matBack.diffuse.z = 1.0f;
	matBack.specular = nullVector;
	matBack.reflective = fullVector;
	matBack.shininess = 0.02f;


	material matFront;
	matFront.diffuse.x = 0.0f;
	matFront.diffuse.y = 1.0f;
	matFront.diffuse.z = 0.0f;
	matFront.specular = nullVector;
	matFront.reflective = nullVector;
	matFront.shininess = 1.0f;



	material matRight;
	matRight.diffuse.x = 1.0f;
	matRight.diffuse.y = 0.0f;
	matRight.diffuse.z = 0.0f;
	matRight.specular = nullVector;
	matRight.reflective = nullVector;
	matRight.shininess = 0.1f;



	material matTop;
	matTop.diffuse.x = 0.4f;
	matTop.diffuse.y = 0.2f;
	matTop.diffuse.z = 0.3f;
	matTop.specular = nullVector;
	matTop.reflective = nullVector;
	matTop.shininess = 0.1f;

	material matSp1;
	matSp1.diffuse.x = 0.0f;
	matSp1.diffuse.y = 1.0f;
	matSp1.diffuse.z = 1.0f;
	matSp1.specular = nullVector;
	matSp1.reflective = medVector;
	matSp1.shininess = 0.5f;

	material matSp2;
	matSp2.diffuse.x = 0.6f;
	matSp2.diffuse.y = 0.6f;
	matSp2.diffuse.z = 0.6f;
	matSp2.specular = hiVector;
	matSp2.reflective = fullVector;
	matSp2.shininess = 0.08f;

	material matSp3;
	matSp3.diffuse.x = 1.0f;
	matSp3.diffuse.y = 1.0f;
	matSp3.diffuse.z = 1.0f;
	matSp3.specular = nullVector;
	matSp3.reflective = nullVector;
	matSp3.shininess = 0.0f;


	xcarVector v1bis( 80.0f, 0.0f, 80.0f);
	xcarVector v2bis( 80.0f, 0.0f,-80.0f);
	xcarVector v3bis(-80.0f, 0.0f,-80.0f);
	xcarVector v4bis(-80.0f, 0.0f, 80.0f);

	xcarVector v1( 40.0f, 0.0f, 40.0f);
	xcarVector v2( 40.0f, 0.0f,-40.0f);
	xcarVector v3(-40.0f, 0.0f,-40.0f);
	xcarVector v4(-40.0f, 0.0f, 40.0f);

	xcarVector v5(-40.0f, 80.0f, 40.0f);
	xcarVector v6( 40.0f, 80.0f, 40.0f);
	xcarVector v7( 40.0f, 80.0f,-40.0f);
	xcarVector v8(-40.0f, 80.0f,-40.0f);

	getFloor(matfloor1, matfloor2, rayTracer->surfaces,-40,-40,40,40,10.0);

	xcarjiTriangleFace *plane3 = new xcarjiTriangleFace(v4,v3,v5,matLeft);
	xcarjiTriangleFace *plane4 = new xcarjiTriangleFace(v5,v3,v8,matLeft);

	xcarjiTriangleFace *plane5 = new xcarjiTriangleFace(v3,v2,v8,matBack);
	xcarjiTriangleFace *plane6 = new xcarjiTriangleFace(v2,v7,v8,matBack);

	xcarjiTriangleFace *plane7 = new xcarjiTriangleFace(v2,v1,v6,matRight);
	xcarjiTriangleFace *plane8 = new xcarjiTriangleFace(v2,v6,v7,matRight);

	xcarjiTriangleFace *plane9 = new xcarjiTriangleFace(v8,v7,v6,matTop);
	xcarjiTriangleFace *plane10 = new xcarjiTriangleFace(v8,v6,v5,matTop);

	xcarjiTriangleFace *plane11 = new xcarjiTriangleFace(v4,v5,v6,matFront, false);
	xcarjiTriangleFace *plane12 = new xcarjiTriangleFace(v4,v6,v1,matFront, false);

	float offsetX1,offsetX2,
	    offsetY1,offsetY2,
	    offsetZ1,offsetZ2,radio;

	radio = 8.0f;

	xcarVector centroMesa1(10.5f,21.0f,21.0f);
	xcarVector centroMesa2(10.5f,21.0f,21.0f);

	offsetX1 = 10.0f;
	offsetY1 = -5.0f;
	offsetZ1 = 10.0f;
	xcarVector offsetM1(offsetX1,offsetY1,offsetZ1);
	offsetX2 = -30.0f;
	offsetY2 = -5.0f;
	offsetZ2 = -30.0f;
	xcarVector offsetM2(offsetX2,offsetY2,offsetZ2);

	xcarVector sphpos1(0.0f,radio,0.0f);
	xcarVector sphpos2(0.0f,radio,0.0f);
	xcarVector sphpos3(0.0f,79.0f,0.0f);

	xcarjiSphere *sphere1 = new xcarjiSphere(radio,sphpos1+offsetM1+centroMesa1,matSp1);
	xcarjiSphere *sphere2 = new xcarjiSphere(radio,sphpos2+offsetM2+centroMesa2,matSp2);
	xcarjiSphere *sphere3 = new xcarjiSphere(0.5f,sphpos3,matSp3);

	rayTracer->surfaces.push_back(plane5);
	rayTracer->surfaces.push_back(plane6);
	rayTracer->surfaces.push_back(plane7);
	rayTracer->surfaces.push_back(plane8);
	rayTracer->surfaces.push_back(plane3);
	rayTracer->surfaces.push_back(plane4);
	rayTracer->surfaces.push_back(plane9);
	rayTracer->surfaces.push_back(plane10);
	rayTracer->surfaces.push_back(plane11);
	rayTracer->surfaces.push_back(plane12);
	rayTracer->surfaces.push_back(sphere1);
	rayTracer->surfaces.push_back(sphere2);
	rayTracer->surfaces.push_back(sphere3);

	getSurfaces(matTable,rayTracer->surfaces,offsetX1,offsetY1,offsetZ1);
	getSurfaces(matTable,rayTracer->surfaces,offsetX2,offsetY2,offsetZ2);

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
