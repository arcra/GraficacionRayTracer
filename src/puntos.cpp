#include <iostream>
#include "puntos.h"
#include "Surfaces.h"
#include "math.h"
using namespace std;
using namespace RayTracing;
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

//vector<Surface> getSurfaces(material mat)
void getSurfaces(material mat, vector<ISurface*> &sur,float offsetX, float offsetY, float offsetZ)
{

  //vector<Surface> sur;
  
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
      Vector3D v1(mesa[i][0]+offsetX,mesa[i][1]+offsetY,mesa[i][2]+offsetZ);        
      Vector3D v2(mesa[i+3][0]+offsetX,mesa[i+3][1]+offsetY,mesa[i+3][2]+offsetZ);
      Vector3D v3(mesa[i+2][0]+offsetX,mesa[i+2][1]+offsetY,mesa[i+2][2]+offsetZ);
      //Surface *s1 = new Surface(v1,v2,v3,&mat,name);
      TriangleFace *s1 = new TriangleFace(v1,v2,v3,mat);
      sur.push_back(s1);
      
      Vector3D v4(mesa[i][0]+offsetX,mesa[i][1]+offsetY,mesa[i][2]+offsetZ);        
      Vector3D v5(mesa[i+2][0]+offsetX,mesa[i+2][1]+offsetY,mesa[i+2][2]+offsetZ);
      Vector3D v6(mesa[i+1][0]+offsetX,mesa[i+1][1]+offsetY,mesa[i+1][2]+offsetZ);
      //Surface *s2 = new Surface(v4,v5,v6,&mat,name);
TriangleFace *s2 = new TriangleFace(v4,v5,v6,mat);
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
      Vector3D v7(mesa[i+1][0]+offsetX,mesa[i+1][1]+offsetY,mesa[i+1][2]+offsetZ);        
      Vector3D v8(mesa[i+2][0]+offsetX,mesa[i+2][1]+offsetY,mesa[i+2][2]+offsetZ);
      Vector3D v9(mesa[i+6][0]+offsetX,mesa[i+6][1]+offsetY,mesa[i+6][2]+offsetZ);
      //Surface *s3 = new Surface(v7,v8,v9,&mat,name);
      //TriangleFace *s1 = new TriangleFace(v1,v2,v3,mat);
    TriangleFace *s3 = new TriangleFace(v7,v8,v9,mat);
      sur.push_back(s3);
      
      Vector3D v10(mesa[i+1][0]+offsetX,mesa[i+1][1]+offsetY,mesa[i+1][2]+offsetZ);        
      Vector3D v11(mesa[i+6][0]+offsetX,mesa[i+6][1]+offsetY,mesa[i+6][2]+offsetZ);
      Vector3D v12(mesa[i+5][0]+offsetX,mesa[i+5][1]+offsetY,mesa[i+5][2]+offsetZ);
      // Surface *s4 = new Surface(v10,v11,v12,&mat,name);
      TriangleFace *s4 = new TriangleFace(v10,v11,v12,mat);
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
      Vector3D v13(mesa[i+4][0]+offsetX,mesa[i+4][1]+offsetY,mesa[i+4][2]+offsetZ);        
      Vector3D v14(mesa[i+7][0]+offsetX,mesa[i+7][1]+offsetY,mesa[i+7][2]+offsetZ);
      Vector3D v15(mesa[i+3][0]+offsetX,mesa[i+3][1]+offsetY,mesa[i+3][2]+offsetZ);
      // Surface *s5 = new Surface(v13,v14,v15,&mat,name);

      TriangleFace *s5 = new TriangleFace(v13,v14,v15,mat);
      sur.push_back(s5);
      
      Vector3D v16(mesa[i+4][0]+offsetX,mesa[i+4][1]+offsetY,mesa[i+4][2]+offsetZ);        
      Vector3D v17(mesa[i+3][0]+offsetX,mesa[i+3][1]+offsetY,mesa[i+3][2]+offsetZ);
      Vector3D v18(mesa[i][0]+offsetX,mesa[i][1]+offsetY,mesa[i][2]+offsetZ);
      // Surface *s6 = new Surface(v16,v17,v18,&mat,name);
      TriangleFace *s6 = new TriangleFace(v16,v17,v18,mat);
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
      Vector3D v19(mesa[i+5][0]+offsetX,mesa[i+5][1]+offsetY,mesa[i+5][2]+offsetZ);        
      Vector3D v20(mesa[i+6][0]+offsetX,mesa[i+6][1]+offsetY,mesa[i+6][2]+offsetZ);
      Vector3D v21(mesa[i+7][0]+offsetX,mesa[i+7][1]+offsetY,mesa[i+7][2]+offsetZ);
      // Surface *s7 = new Surface(v19,v20,v21,&mat,name);
      
      TriangleFace *s7 = new TriangleFace(v19,v20,v21,mat);
      sur.push_back(s7);
      
      Vector3D v22(mesa[i+5][0]+offsetX,mesa[i+5][1]+offsetY,mesa[i+5][2]+offsetZ);        
      Vector3D v23(mesa[i+7][0]+offsetX,mesa[i+7][1]+offsetY,mesa[i+7][2]+offsetZ);
      Vector3D v24(mesa[i+4][0]+offsetX,mesa[i+4][1]+offsetY,mesa[i+4][2]+offsetZ);
      TriangleFace *s8 = new TriangleFace(v22,v23,v24,mat);
      //  Surface *s8 = new Surface(v22,v23,v24,&mat,name);
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
      Vector3D v25(mesa[i+4][0]+offsetX,mesa[i+4][1]+offsetY,mesa[i+4][2]+offsetZ);        
      Vector3D v26(mesa[i][0]+offsetX,mesa[i][1]+offsetY,mesa[i][2]+offsetZ);
      Vector3D v27(mesa[i+1][0]+offsetX,mesa[i+1][1]+offsetY,mesa[i+1][2]+offsetZ);
      TriangleFace *s9 = new TriangleFace(v25,v26,v27,mat);
      //   Surface *s9 = new Surface(v25,v26,v27,&mat,name);
      sur.push_back(s9);
      
      Vector3D v28(mesa[i+4][0]+offsetX,mesa[i+4][1]+offsetY,mesa[i+4][2]+offsetZ);        
      Vector3D v29(mesa[i+1][0]+offsetX,mesa[i+1][1]+offsetY,mesa[i+1][2]+offsetZ);
      Vector3D v30(mesa[i+5][0]+offsetX,mesa[i+5][1]+offsetY,mesa[i+5][2]+offsetZ);
      TriangleFace *s10 = new TriangleFace(v28,v29,v30,mat);
      //Surface *s10 = new Surface(v28,v29,v30,&mat,name);
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
	  Vector3D v31(mesa[i+3][0]+offsetX,mesa[i+3][1]+offsetY,mesa[i+3][2]+offsetZ);        
	  Vector3D v32(mesa[i+7][0]+offsetX,mesa[i+7][1]+offsetY,mesa[i+7][2]+offsetZ);
	  Vector3D v33(mesa[i+6][0]+offsetX,mesa[i+6][1]+offsetY,mesa[i+6][2]+offsetZ);
	  TriangleFace *s11 = new TriangleFace(v31,v32,v33,mat);
	  // Surface *s11 = new Surface(v31,v32,v33,&mat,name);
	  sur.push_back(s11);
      
	  Vector3D v34(mesa[i+3][0]+offsetX,mesa[i+3][1]+offsetY,mesa[i+3][2]+offsetZ);        
	  Vector3D v35(mesa[i+6][0]+offsetX,mesa[i+6][1]+offsetY,mesa[i+6][2]+offsetZ);
	  Vector3D v36(mesa[i+2][0]+offsetX,mesa[i+2][1]+offsetY,mesa[i+2][2]+offsetZ);
	  TriangleFace *s12 = new TriangleFace(v34,v35,v36,mat);
	  // Surface *s12 = new Surface(v34,v35,v36,&mat,name);
	  sur.push_back(s12); 	  
	  
    }

  //return sur;

}

void getFloor(material mat1, material mat2, std::vector<ISurface*> &sur, float xmin, float zmin, float xmax, float zmax, float nMos)
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
	  Vector3D v1(x1,0.0f,z1);
	  Vector3D v2(x2,0.0f,z1);
	  Vector3D v3(x1,0.0f,z2);
	  Vector3D v4(x2,0.0f,z2);

	  if((i+j) % 2 == 0)/*Para los materiales*/
	    {
	      // TriangleFace t1 (v1,v2,v3,mat1);
	      // TriangleFace t2(v2,v4,v3,mat1);
	      sur.push_back(new TriangleFace(v1,v2,v3,mat1));
	      sur.push_back(new TriangleFace(v2,v4,v3,mat1));
	    }
	  else
	    {
	      /*TriangleFace t1(v1,v2,v3,mat2);
	      TriangleFace t1(v2,v4,v3,mat2);
	      surface.push_back(t1);
	      surface.push_back(t2);*/
	      sur.push_back(new TriangleFace(v1,v2,v3,mat2));
	      sur.push_back(new TriangleFace(v2,v4,v3,mat2));
	    }
	  x1 = x1 + deltaX;
	}

      z1 = z1 + deltaZ;
    }



}
