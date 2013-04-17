#include <iostream>
#include "puntos.h"
#include "xcarjiSurfaces.h"
#include "math.h"
using namespace std;
using namespace xcarjiRayTracing;
/*material mat1;
  material mat2;*/

/* Distribucion normal de cada paralelepípedo de la mesa
     a'-----------b' 
    /|           /|
   / |          / |
  a ---------- b  |
  |  d'--------|--c'
  | /          | /
  |/           |/ 
  d----------- c
*/
float mesa[72][3] = {
  {0, 21, 0},  // a   //Elemento 0: inicio cubierta mesa 
  {21, 21, 0}, // b
  {21, 18, 0}, // c
  {0, 18, 0},  // d 
  {0, 21, 42}, // a'
  {21, 21, 42},// b'
  {21, 18, 42},// c'
  {0, 18, 42}, // d' //Elemento 7: fin cubierta mesa
  {1.5, 18, 1.5},//Elemento 8: inicio pata 1
  {5.4, 18, 1.5},
  {5.4, 0, 1.5},
  {1.5, 0, 1.5},
  {1.5, 18, 5.4},
  {5.4, 18, 5.4},
  {5.4, 0, 5.4},
  {1.5, 0, 5.4}, //Elemento 15: inicio pata 1
  {5.4, 18, 1.5}, //Elemento 16: inicio travesaño 1: es {5.4, 18, 1.5}
  {15.6, 18, 1.5},
  {15.6, 15, 1.5},
  {5.4, 15, 1.5},
  {5.4, 18, 5.4},
  {15.6, 18, 5.4},
  {15.6, 15, 5.4},
  {5.4, 15, 5.4}, //Elemento 23: fin travesaño 1
  {15.6, 18, 1.5}, //Elemento 24: inicio pata 2
  {19.5, 18, 1.5},
  {19.5, 0, 1.5},
  {15.6, 0, 1.5},
  {15.6, 18, 5.4},
  {19.5, 18, 5.4},
  {19.5, 0, 5.4},
  {15.6, 0, 5.4}, //Elemento 31: fin pata 2
  {1.5, 18, 5.4}, //Elemento 32: inicio travesaño 2
  {5.4, 18, 5.4},
  {5.4, 15, 5.4},
  {1.5, 15, 5.4},
  {1.5, 18, 36.6},
  {5.4, 18, 36.6},
  {5.4, 15, 36.6},
  {1.5, 15, 36.6}, //Elemento 39: fin travesaño 2
  {15.6, 18, 5.4}, //Elemento 40: inicio travesaño 3
  {19.5, 18, 5.4},
  {19.5, 15, 5.4},
  {15.6, 15, 5.4},
  {15.6, 18, 36.6},
  {19.5, 18, 36.6},
  {19.5, 15, 36.6},
  {15.6, 15, 36.6}, //Elemento 47: inicio travesaño 3
  {1.5, 18, 36.6}, //Elemento 48: inicio pata 3
  {5.4, 18, 36.6},
  {5.4, 0, 36.6},
  {1.5, 0, 36.6},
  {1.5, 18, 40.5},
  {5.4, 18, 40.5},
  {5.4, 0, 40.5},
  {1.5, 0, 40.5}, //Elemento 55: fin pata 3
  {5.4, 18, 36.6}, //Elemento 56: inicio travesaño 4
  {15.6, 18, 36.6},
  {15.6, 15, 36.6},
  {5.4, 15, 36.6},
  {5.4, 18, 40.5},
  {15.6, 18, 40.5},
  {15.6, 15, 40.5},
  {5.4, 15, 40.5}, //Elemento 63: fin travesaño 4
  {15.6, 18, 36.6}, //Elemento 64: inicio pata 4
  {19.5, 18, 36.6},
  {19.5, 0, 36.6},
  {15.6, 0, 36.6},
  {15.6, 18, 40.5},
  {19.5, 18, 40.5},
  {19.5, 0, 40.5},
  {15.6, 0, 40.5} //Elemento 71: fin pata 4
}; 

float centroCubiertaMesa[1][3] = {{10.5, 21, 21}}; //se utilizará para fijar la esfera

/*
float habitacion[8][3] = {
  {-40, 80, 40},  // a   //Elemento 0: inicio habitacion
  {40, 80, 40}, // b
  {40, 0, 40}, // c
  {-40, 0, 40},  // d 
  {-40, 80, -40}, // a'
  {40, 80, -40},// b'
  {40, 0, -40},// c'
  {-40, 0, -40}, // d' //Elemento 7: fin habitacion
}; 

float centroPisoHabitacion[1][3] = {0, 0, 0};
*/

//vector<xcarSurface> getSurfaces(material mat)
void getSurfaces(material mat, vector<xcarjiISurface*> &sur,float offsetX, float offsetY, float offsetZ)
{

  //vector<xcarSurface> sur;
  
  for(int i = 0; i < 72 ; i = i + 8)
    {
      /* Vista frontal
         4------------5 
        /|           /|
       / |          / |
      0----------- 1  |
      |  7---------|--6
      | /          | /
      |/           |/ 
      3----------- 2
      */	
      xcarVector v1(mesa[i][0]+offsetX,mesa[i][1]+offsetY,mesa[i][2]+offsetZ);        
      xcarVector v2(mesa[i+3][0]+offsetX,mesa[i+3][1]+offsetY,mesa[i+3][2]+offsetZ);
      xcarVector v3(mesa[i+2][0]+offsetX,mesa[i+2][1]+offsetY,mesa[i+2][2]+offsetZ);
      //xcarSurface *s1 = new xcarSurface(v1,v2,v3,&mat,name);
      xcarjiTriangleFace *s1 = new xcarjiTriangleFace(v1,v2,v3,mat);
      sur.push_back(s1);
      
      xcarVector v4(mesa[i][0]+offsetX,mesa[i][1]+offsetY,mesa[i][2]+offsetZ);        
      xcarVector v5(mesa[i+2][0]+offsetX,mesa[i+2][1]+offsetY,mesa[i+2][2]+offsetZ);
      xcarVector v6(mesa[i+1][0]+offsetX,mesa[i+1][1]+offsetY,mesa[i+1][2]+offsetZ);
      //xcarSurface *s2 = new xcarSurface(v4,v5,v6,&mat,name);
xcarjiTriangleFace *s2 = new xcarjiTriangleFace(v4,v5,v6,mat);
	  sur.push_back(s2);  
	  	  
	  	  
      /* Vista lateral derecha
         0------------4 
        /|           /|
       / |          / |
      1----------- 5  |
      |  3---------|--7
      | /          | /
      |/           |/ 
      2----------- 6
      */	  	  
      xcarVector v7(mesa[i+1][0]+offsetX,mesa[i+1][1]+offsetY,mesa[i+1][2]+offsetZ);        
      xcarVector v8(mesa[i+2][0]+offsetX,mesa[i+2][1]+offsetY,mesa[i+2][2]+offsetZ);
      xcarVector v9(mesa[i+6][0]+offsetX,mesa[i+6][1]+offsetY,mesa[i+6][2]+offsetZ);
      //xcarSurface *s3 = new xcarSurface(v7,v8,v9,&mat,name);
      //xcarjiTriangleFace *s1 = new xcarjiTriangleFace(v1,v2,v3,mat);
    xcarjiTriangleFace *s3 = new xcarjiTriangleFace(v7,v8,v9,mat);
      sur.push_back(s3);
      
      xcarVector v10(mesa[i+1][0]+offsetX,mesa[i+1][1]+offsetY,mesa[i+1][2]+offsetZ);        
      xcarVector v11(mesa[i+6][0]+offsetX,mesa[i+6][1]+offsetY,mesa[i+6][2]+offsetZ);
      xcarVector v12(mesa[i+5][0]+offsetX,mesa[i+5][1]+offsetY,mesa[i+5][2]+offsetZ);
      // xcarSurface *s4 = new xcarSurface(v10,v11,v12,&mat,name);
      xcarjiTriangleFace *s4 = new xcarjiTriangleFace(v10,v11,v12,mat);
	  sur.push_back(s4);  	  
	  
	  
      /* Vista lateral izquierda
         5------------1 
        /|           /|
       / |          / |
      4----------- 0  |
      |  6---------|--2
      | /          | /
      |/           |/ 
      7----------- 3
      */	
      xcarVector v13(mesa[i+4][0]+offsetX,mesa[i+4][1]+offsetY,mesa[i+4][2]+offsetZ);        
      xcarVector v14(mesa[i+7][0]+offsetX,mesa[i+7][1]+offsetY,mesa[i+7][2]+offsetZ);
      xcarVector v15(mesa[i+3][0]+offsetX,mesa[i+3][1]+offsetY,mesa[i+3][2]+offsetZ);
      // xcarSurface *s5 = new xcarSurface(v13,v14,v15,&mat,name);

      xcarjiTriangleFace *s5 = new xcarjiTriangleFace(v13,v14,v15,mat);
      sur.push_back(s5);
      
      xcarVector v16(mesa[i+4][0]+offsetX,mesa[i+4][1]+offsetY,mesa[i+4][2]+offsetZ);        
      xcarVector v17(mesa[i+3][0]+offsetX,mesa[i+3][1]+offsetY,mesa[i+3][2]+offsetZ);
      xcarVector v18(mesa[i][0]+offsetX,mesa[i][1]+offsetY,mesa[i][2]+offsetZ);
      // xcarSurface *s6 = new xcarSurface(v16,v17,v18,&mat,name);
      xcarjiTriangleFace *s6 = new xcarjiTriangleFace(v16,v17,v18,mat);
	  sur.push_back(s6);  	 
	  	       
      
      /* Vista trasera
         1------------0 
        /|           /|
       / |          / |
      5------------4  |
      |  2---------|--3
      | /          | /
      |/           |/ 
      6------------7
      */	
      xcarVector v19(mesa[i+5][0]+offsetX,mesa[i+5][1]+offsetY,mesa[i+5][2]+offsetZ);        
      xcarVector v20(mesa[i+6][0]+offsetX,mesa[i+6][1]+offsetY,mesa[i+6][2]+offsetZ);
      xcarVector v21(mesa[i+7][0]+offsetX,mesa[i+7][1]+offsetY,mesa[i+7][2]+offsetZ);
      // xcarSurface *s7 = new xcarSurface(v19,v20,v21,&mat,name);
      
      xcarjiTriangleFace *s7 = new xcarjiTriangleFace(v19,v20,v21,mat);
      sur.push_back(s7);
      
      xcarVector v22(mesa[i+5][0]+offsetX,mesa[i+5][1]+offsetY,mesa[i+5][2]+offsetZ);        
      xcarVector v23(mesa[i+7][0]+offsetX,mesa[i+7][1]+offsetY,mesa[i+7][2]+offsetZ);
      xcarVector v24(mesa[i+4][0]+offsetX,mesa[i+4][1]+offsetY,mesa[i+4][2]+offsetZ);
      xcarjiTriangleFace *s8 = new xcarjiTriangleFace(v22,v23,v24,mat);
      //  xcarSurface *s8 = new xcarSurface(v22,v23,v24,&mat,name);
	  sur.push_back(s8); 
	  
	  
      /* Vista superior
         7------------6 
        /|           /|
       / |          / |
      4------------5  |
      |  3---------|--2
      | /          | /
      |/           |/ 
      0------------1
      */	
      xcarVector v25(mesa[i+4][0]+offsetX,mesa[i+4][1]+offsetY,mesa[i+4][2]+offsetZ);        
      xcarVector v26(mesa[i][0]+offsetX,mesa[i][1]+offsetY,mesa[i][2]+offsetZ);
      xcarVector v27(mesa[i+1][0]+offsetX,mesa[i+1][1]+offsetY,mesa[i+1][2]+offsetZ);
      xcarjiTriangleFace *s9 = new xcarjiTriangleFace(v25,v26,v27,mat);
      //   xcarSurface *s9 = new xcarSurface(v25,v26,v27,&mat,name);
      sur.push_back(s9);
      
      xcarVector v28(mesa[i+4][0]+offsetX,mesa[i+4][1]+offsetY,mesa[i+4][2]+offsetZ);        
      xcarVector v29(mesa[i+1][0]+offsetX,mesa[i+1][1]+offsetY,mesa[i+1][2]+offsetZ);
      xcarVector v30(mesa[i+5][0]+offsetX,mesa[i+5][1]+offsetY,mesa[i+5][2]+offsetZ);
      xcarjiTriangleFace *s10 = new xcarjiTriangleFace(v28,v29,v30,mat);
      //xcarSurface *s10 = new xcarSurface(v28,v29,v30,&mat,name);
      sur.push_back(s10); 	  
	  
	  
      /* Vista inferior
         0------------1 
        /|           /|
       / |          / |
      3------------2  |
      |  4---------|--5
      | /          | /
      |/           |/ 
      7------------6
      */	
	  xcarVector v31(mesa[i+3][0]+offsetX,mesa[i+3][1]+offsetY,mesa[i+3][2]+offsetZ);        
	  xcarVector v32(mesa[i+7][0]+offsetX,mesa[i+7][1]+offsetY,mesa[i+7][2]+offsetZ);
	  xcarVector v33(mesa[i+6][0]+offsetX,mesa[i+6][1]+offsetY,mesa[i+6][2]+offsetZ);
	  xcarjiTriangleFace *s11 = new xcarjiTriangleFace(v31,v32,v33,mat);
	  // xcarSurface *s11 = new xcarSurface(v31,v32,v33,&mat,name);
	  sur.push_back(s11);
      
	  xcarVector v34(mesa[i+3][0]+offsetX,mesa[i+3][1]+offsetY,mesa[i+3][2]+offsetZ);        
	  xcarVector v35(mesa[i+6][0]+offsetX,mesa[i+6][1]+offsetY,mesa[i+6][2]+offsetZ);
	  xcarVector v36(mesa[i+2][0]+offsetX,mesa[i+2][1]+offsetY,mesa[i+2][2]+offsetZ);
	  xcarjiTriangleFace *s12 = new xcarjiTriangleFace(v34,v35,v36,mat);
	  // xcarSurface *s12 = new xcarSurface(v34,v35,v36,&mat,name);
	  sur.push_back(s12); 	  
	  
    }

  //return sur;

}

void getFloor(material mat1, material mat2, std::vector<xcarjiISurface*> &sur, float xmin, float zmin, float xmax, float zmax, float nMos)
{
  if(nMos <= 0.0)
    {
      nMos = 1.0;
    }

 



  float distX = fabs(xmax - xmin);
  float distZ = fabs(zmax - zmin);
  

  float deltaX = distX/nMos;
  float deltaZ = distZ/nMos;
  
 
  float x1,z1;
  float x2,z2;
   x1 = xmin;
  z1 = zmin;
  
  for(int j = 0 ; j < nMos; j++)
    {
      x1 = xmin;
      for(int i = 0; i < nMos; i++)
	{
	  x2 = x1 + deltaX;
	  z2 = z1 + deltaZ;
	  xcarVector v1(x1,0.0f,z1);
	  xcarVector v2(x2,0.0f,z1);
	  xcarVector v3(x1,0.0f,z2);
	  xcarVector v4(x2,0.0f,z2);

	  if((i+j) % 2 == 0)/*Para los materiales*/
	    {
	      // xcarjiTriangleFace t1 (v1,v2,v3,mat1);
	      // xcarjiTriangleFace t2(v2,v4,v3,mat1);
	      sur.push_back(new xcarjiTriangleFace(v1,v2,v3,mat1));
	      sur.push_back(new xcarjiTriangleFace(v2,v4,v3,mat1));
	    }
	  else
	    {
	      /*xcarjiTriangleFace t1(v1,v2,v3,mat2);
	      xcarjiTriangleFace t1(v2,v4,v3,mat2);
	      surface.push_back(t1);
	      surface.push_back(t2);*/
	      sur.push_back(new xcarjiTriangleFace(v1,v2,v3,mat2));
	      sur.push_back(new xcarjiTriangleFace(v2,v4,v3,mat2));
	    }
	  x1 = x1 + deltaX;
	}

      z1 = z1 + deltaZ;
    }



}
