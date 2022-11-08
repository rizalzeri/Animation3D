
#include <math.h> 
#include <GL/glut.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <assert.h>
#include <fstream>
#include "imageloader.h"

#define EN_SIZE 20
GLuint _textureId, _textureIdDepan, _textureIdKanan, _textureIdBelakang, _textureIdKiri, _textureIdAtas; //ID OpenGL untuk tekstur
float angle=0.0, deltaAngle = 0.0, ratio; 
const float Z_MIN = -500, Z_MAX = 500; 
const float X_MIN = -500, X_MAX = 500; 
const float gap = 10; 
float x=0.0f,y=30.0f,z=60.0f; // posisi awal kamera 
float lx=0.0f,ly=-0.5f,lz=-1.f; 
int deltaMove = 0,h,w; 
static int rotAngleX =-20, rotAngleY =160, rotAngleZ =0;
float panjang, lebar, tinggi;
const double PI = 3.141592653589793;
int i;

GLuint loadTexture(Image* image) {
	// Fungsi menginisialisasi ID OpenGL tekstur
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}


void Reshape(int w1, int h1) 
{ 
	// Fungsi reshape 
	if(h1 == 0) h1 = 1; 
	w = w1; 
	h = h1; 
	ratio = 1.0f * w / h; 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glViewport(0, 0, w, h); 
	gluPerspective(45,ratio,0.1,1000); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f); 
} 

void orientMe(float ang) 
{ 
	// Fungsi ini untuk memutar arah kamera (tengok kiri/kanan) 
	lx = sin(ang); 
	lz = -cos(ang); 
	glLoadIdentity(); 
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f); 
} 

void moveMeFlat(int i) 
{ 
	// Fungsi ini untuk maju mundur kamera 
	x = x + i*(lx)*0.5; 
	z = z + i*(lz)*0.5; 
	glLoadIdentity(); 
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f); 
} 

 
void pressKey(int key, int x, int y) { 
 	// Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas 
 	// Selama tombol ditekan, variabel angle dan move diubah => kamera bergerak 
 	switch (key) { 
 		case GLUT_KEY_LEFT : deltaAngle = -0.1f;break; 
 		case GLUT_KEY_RIGHT : deltaAngle = 0.1f;break; 
 		case GLUT_KEY_UP : deltaMove = 1;break; 
 		case GLUT_KEY_DOWN : deltaMove = -1;break; 
 	} 
} 

void releaseKey(int key, int x, int y) { 
 	// Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas 
 	// Saat tombol dilepas, variabel angle dan move diset nol => kamera berhenti 
 	switch (key) { 
 		case GLUT_KEY_LEFT : if (deltaAngle < 0.0f) 
			deltaAngle = 0.0f; 
 			break; 
 		case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f) 
 			deltaAngle = 0.0f; 
			break; 
 		case GLUT_KEY_UP : if (deltaMove > 0) 
			deltaMove = 0; 
 			break; 
		case GLUT_KEY_DOWN : if (deltaMove < 0) 
 			deltaMove = 0; 
			break; 
 	} 
}

//////////////////////// Fungsi Untuk Membuat Roda //////////////////////////
void Roda(float x_roda, float y_roda, float z_roda) {
    glPushMatrix();
    glRotated(90, 0, 0, 1);
	glTranslatef(x_roda,y_roda,z_roda);
	glScalef(3.,3.,3.);
    glColor3ub(40, 40,40);
        // Kanan Kiri Roda
        glPushMatrix();
            glBegin(GL_TRIANGLE_FAN);
            for (int a = 0; a <= 360; a+=1){
                glVertex3f(cos(a), 1, sin(a));
            }
            glEnd();
        glPopMatrix();
            
        glPushMatrix();
            glTranslatef(0.0, 1.0, 0.0);
            glBegin(GL_TRIANGLE_FAN);
            for (int a = 0; a <= 360; a+=1){
                glVertex3f(cos(a), 1, sin(a));
            }
            glEnd();
        glPopMatrix();
            
        // Tengah Roda
        glPushMatrix();    
            int b;
            glColor3ub(10, 10, 10);
            glTranslatef(0.0, 1.0, 0.0);
            glBegin(GL_QUAD_STRIP);
            for (b=0; b<=360; b+=1){
                glVertex3f(cos(b), +1, sin(b));
                glVertex3f(cos(b), 0, sin(b));
            }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}
void TrukDepan(){
	/////////////// Sisi Kiri ///////////////////////
	glPushMatrix();
	glScalef(2,2,2);
	glRotated(-90,0,1,0);
	glTranslatef(-10,-0.7,2);
	glColor3ub(20,20,20);
	glBegin(GL_TRIANGLE_STRIP);
	// Kaca
	glVertex2f(4,4.3);
	glVertex2f(4,3.7);
	glVertex2f(6,4.6);
	glVertex2f(8,3.5);
	glVertex2f(8,4.7);
	glVertex2f(12.1,3.3);
	glEnd();
	// Body
		glColor3ub(100,100,100);
		glBegin(GL_QUADS);
		// Bawah Belakang
		glVertex2f(0,4);
		glVertex2f(0.3,2.4);
		glVertex2f(4,2.3);
		glVertex2f(4,3.7);
		// Bawah Tengah
		glVertex2f(4,2.3);
		glVertex2f(4,3.7);
		glVertex2f(12.1,3.3);
		glVertex2f(12,2.2);
		// Bawah Depan
		glVertex2f(12.1,3.3);
		glVertex2f(12,2.2);
		glVertex2f(13.8,2.2);
		glVertex2f(14,3);
		// Depan Atas
		glVertex2f(12.1,3.3);
		glVertex2f(14,3);
		glVertex2f(8,5);
		glVertex2f(8,4.7);
		// Atas Tengah
		glVertex2f(8,5);
		glVertex2f(8,4.7);
		glVertex2f(6,4.6);
		glVertex2f(6,5);
		// Belakang Tengah
		glVertex2f(6,4.6);
		glVertex2f(6,5);
		glVertex2f(4,4.7);
		glVertex2f(4,4.3);
		// Belakang Atas
		glVertex2f(4,4.7);
		glVertex2f(4,4.3);
		glVertex2f(4,3.7);
		glVertex2f(0,4);
		// Outline Bawah
		glColor3ub(15,15,15);
		glVertex2f(0.3,2.4);
		glVertex2f(0.5,1.4);
		glVertex2f(13.6,1.4);
		glVertex2f(13.8,2.2);
		glEnd();
	glPopMatrix();
	
	/////////////////// Sisi Kanan ///////////////////////
	glPushMatrix();
	glScalef(2,2,2);
	glRotated(-90,0,1,0);
	glTranslatef(-10,-0.7,-2);
	glColor3ub(20,20,20);
	glBegin(GL_TRIANGLE_STRIP);
	// Kaca
	glVertex2f(4,4.3);
	glVertex2f(4,3.7);
	glVertex2f(6,4.6);
	glVertex2f(8,3.5);
	glVertex2f(8,4.7);
	glVertex2f(12.1,3.3);
	glEnd();
	// Body
		glColor3ub(100,100,100);
		glBegin(GL_QUADS);
		// Bawah Belakang
		glVertex2f(0,4);
		glVertex2f(0.3,2.4);
		glVertex2f(4,2.3);
		glVertex2f(4,3.7);
		// Bawah Tengah
		glVertex2f(4,2.3);
		glVertex2f(4,3.7);
		glVertex2f(12.1,3.3);
		glVertex2f(12,2.2);
		// Bawah Depan
		glVertex2f(12.1,3.3);
		glVertex2f(12,2.2);
		glVertex2f(13.8,2.2);
		glVertex2f(14,3);
		// Depan Atas
		glVertex2f(12.1,3.3);
		glVertex2f(14,3);
		glVertex2f(8,5);
		glVertex2f(8,4.7);
		// Atas Tengah
		glVertex2f(8,5);
		glVertex2f(8,4.7);
		glVertex2f(6,4.6);
		glVertex2f(6,5);
		// Belakang Tengah
		glVertex2f(6,4.6);
		glVertex2f(6,5);
		glVertex2f(4,4.7);
		glVertex2f(4,4.3);
		// Belakang Atas
		glVertex2f(4,4.7);
		glVertex2f(4,4.3);
		glVertex2f(4,3.7);
		glVertex2f(0,4);
		// Outline Bawah
		glColor3ub(15,15,15);
		glVertex2f(0.3,2.4);
		glVertex2f(0.5,1.4);
		glVertex2f(13.6,1.4);
		glVertex2f(13.8,2.2);
		glEnd();
	glPopMatrix();
	//////////// PENUTUP /////////////
	glPushMatrix();
		glTranslatef(4,-1.4,-20);
		glRotated(-90,0,1,0);
		glScalef(2,2,2);
		glColor3ub(110,110,110);
		glBegin(GL_QUADS);
			// Depan
			glVertex3f(13.8,2.2,0);
			glVertex3f(13.8,2.2,4);
			glVertex3f(14,3,4);
			glVertex3f(14,3,0);
			// Depan Atas
			glVertex3f(14,3,4);
			glVertex3f(14,3,0);
			glVertex3f(13,3.3,0);
			glVertex3f(13,3.3,4);
			// Belakang Atas
			glVertex3f(6,5,0);
			glVertex3f(6,5,4);
			glVertex3f(0,4,4);
			glVertex3f(0,4,0);
			// Bawah
			glVertex3f(0.5,1.4,0);
			glVertex3f(0.5,1.4,4);
			glVertex3f(13.6,1.4,4);
			glVertex3f(13.6,1.4,0);
			// Kaca Depan
			glColor3ub(20,20,20);
			glVertex3f(13,3.3,0);
			glVertex3f(13,3.3,4);
			glVertex3f(8,5,4);
			glVertex3f(8,5,0);
			// Bumper Depan
			glColor3ub(5,5,5);
			glVertex3f(13.6,1.4,0);
			glVertex3f(13.6,1.4,4);
			glVertex3f(13.8,2.2,4);
			glVertex3f(13.8,2.2,0);
			// Lampu Belakang
			glColor3ub(175,69,42);
			glVertex3f(0.3,2.4,0);
			glVertex3f(0.3,2.4,4);
			glVertex3f(0.5,1.4,4);
			glVertex3f(0.5,1.4,0);
			// Belakang
			glColor3ub(1,133,121);
			glVertex3f(0,4,4);
			glVertex3f(0,4,0);
			glVertex3f(0.3,2.4,0);
			glVertex3f(0.3,2.4,4);
			// Atap
			glVertex3f(8,5,4);
			glVertex3f(8,5,0);
			glVertex3f(6,5,0);
			glVertex3f(6,5,4);
		glEnd();
	glPopMatrix();
	///////////////////Roda//////////////////////
	Roda(3.2,1,1.9);
	Roda(3.2,-10,1.9);
	Roda(3.2,1,-15);
	Roda(3.2,-10,-15);
	///////////////// Pengait //////////////////
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(2,2,2);
	glRotated(90,0,1,0);
	glTranslatef(7.5,0,-0.5);
	glBegin(GL_QUADS);
		glVertex3f(1,1,0);
		glVertex3f(1,1,1);
		glVertex3f(1,2,1);
		glVertex3f(1,2,0);
		
		glVertex3f(1,2,1);
		glVertex3f(1,2,0);
		glVertex3f(7,2,0);
		glVertex3f(7,2,1);
		
		glVertex3f(7,2,0);
		glVertex3f(7,2,1);
		glVertex3f(7,1,1);
		glVertex3f(7,1,0);
		
		glVertex3f(7,1,1);
		glVertex3f(7,1,0);
		glVertex3f(1,1,0);
		glVertex3f(1,1,1);
		
		glVertex3f(7,2,0);
	    glVertex3f(7,1,0);
	    glVertex3f(1,1,0);
	    glVertex3f(1,2,0);
	    
	    glVertex3f(1,1,1);
		glVertex3f(1,2,1);
		glVertex3f(7,2,1);
		glVertex3f(7,1,1);
	glEnd();
	glPopMatrix();
}

void TrukBelakang() 
{
 	// Kiri
	glPushMatrix();
	glTranslatef(-5,0,-23);
	glScalef(2,2,2);
	glRotated(-90,0,1,0);
	glColor3ub(35,35,35);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-1.3,3.,0.); // Titik Tengah Depan
	glVertex3f(-4.5,7.,0.); // titik Atas Depan
	glVertex3f(-2.5,2.,0.); // Titik Bawah Depan
	glVertex3f(-14.,7.,0.); // Titik Atas Belakang
	glVertex3f(-12.,2.,0.); // Titik Bawah Tengah
	glVertex3f(-14.,2.,0.); // Titik Bawah Belakang
	glEnd();
	// Outline Kiri
	glBegin(GL_QUADS);
	glColor3ub(155,155,155);
		// Bawah
		glVertex3f(-15,1,0);
		glVertex3f(-15,2,0);
		glVertex3f(-1,2,0);
		glVertex3f(-2,1,0);
		// Depan Bawah
		glVertex3f(-2.5,2,0);
		glVertex3f(-1,2,0);
		glVertex3f(0,3,0);
		glVertex3f(-1.3,3,0);
		// Depan Atas
		glVertex3f(0,3,0);
		glVertex3f(-1.3,3,0);
		glVertex3f(-4.5,7,0);
		glVertex3f(-4,8,0);
		// Atas
		glVertex3f(-4.5,7,0);
		glVertex3f(-4,8,0);
		glVertex3f(-15,8,0);
		glVertex3f(-14,7,0);
		// Belakang
		glVertex3f(-15,8,0);
		glVertex3f(-14,7,0);
		glVertex3f(-14,2,0);
		glVertex3f(-15,2,0);
	glEnd();
	glPopMatrix();
	
	// Kanan
	glPushMatrix();
	glTranslatef(5,0,-23);
	glScalef(2,2,2);
	glRotated(-90,0,1,0);
	glColor3ub(35,35,35);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-1.3,3.,0.); // Titik Tengah Depan
	glVertex3f(-4.5,7.,0.); // titik Atas Depan
	glVertex3f(-2.5,2.,0.); // Titik Bawah Depan
	glVertex3f(-14.,7.,0.); // Titik Atas Belakang
	glVertex3f(-12.,2.,0.); // Titik Bawah Tengah
	glVertex3f(-14.,2.,0.); // Titik Bawah Belakang
	glEnd();
	// Outline Kanan
	glBegin(GL_QUADS);
	glColor3ub(155,155,155);
		// Bawah
		glVertex3f(-15,1,0);
		glVertex3f(-15,2,0);
		glVertex3f(-1,2,0);
		glVertex3f(-2,1,0);
		// Depan Bawah
		glVertex3f(-2.5,2,0);
		glVertex3f(-1,2,0);
		glVertex3f(0,3,0);
		glVertex3f(-1.3,3,0);
		// Depan Atas
		glVertex3f(0,3,0);
		glVertex3f(-1.3,3,0);
		glVertex3f(-4.5,7,0);
		glVertex3f(-4,8,0);
		// Atas
		glVertex3f(-4.5,7,0);
		glVertex3f(-4,8,0);
		glVertex3f(-15,8,0);
		glVertex3f(-14,7,0);
		// Belakang
		glVertex3f(-15,8,0);
		glVertex3f(-14,7,0);
		glVertex3f(-14,2,0);
		glVertex3f(-15,2,0);
	glEnd();
	glPopMatrix();
	
	//////////// Penutup /////////////
	glPushMatrix();
	glTranslatef(-5,0,-23);
	glScalef(2,2,2);
	glBegin(GL_QUADS);
	// Depan Bawah
	glVertex3f(0.,3.,0.);
	glVertex3f(5.,3.,0.);
	glVertex3f(5.,1.,-2.);
	glVertex3f(0.,1.,-2.);
	// Depan Atas
	glColor3ub(35,35,35);
	glVertex3f(0.,3.,0.);
	glVertex3f(0.,8.,-4.);
	glVertex3f(5.,8.,-4.);
	glVertex3f(5.,3.,0.);
	// Atas
	glVertex3f(0.,8.,-4.);
	glVertex3f(5.,8.,-4.);
	glVertex3f(5.,8.,-15.);
	glVertex3f(0.,8.,-15.);
	// Belakang
	glColor3ub(15,15,15);
	glVertex3f(0.,7.,-15.);
	glVertex3f(5.,7.,-15.);
	glVertex3f(5.,2.,-15.);
	glVertex3f(0.,2.,-15.);
	// Outline Belakang
	glColor3ub(170,170,0);
	glVertex3f(0.,7.,-15.);
	glVertex3f(5.,7.,-15.);
	glVertex3f(5.,8.,-15.);
	glVertex3f(0.,8.,-15.);
	
	glVertex3f(5.,2.,-15.);
	glVertex3f(0.,2.,-15.);
	glVertex3f(0.,1.,-15.);
	glVertex3f(5.,1.,-15.);
	// Bawah
	glColor3ub(120,70,140);
	glVertex3f(0.,1.,-15.);
	glVertex3f(5.,1.,-15.);
	glVertex3f(5.,1.,-2.);
	glVertex3f(0.,1.,-2.); 
	glEnd();
	glPopMatrix();
	/////////////// Roda ////////////
	Roda(3.2,2,-48);
	Roda(3.2,-11,-48); 
	Roda(3.2,2,-31);
	Roda(3.2,-11,-31); 
}
int belok = 0;
float angTrukDepan = 0.0;

//Pergerakan pada Truk //////////////////////////////////////////////////////

float posXTruk = 0.0, posZTruk = 0.0;

void TrukMove()
{
	//Belok kanan
	if (belok == -1){
		if (angTrukDepan >= -10){
			angTrukDepan -= 2;
		}
		if (angTrukDepan < -9.9){
			belok = -2;
		}
	}
	if (belok <= -2){
		if (angTrukDepan <= -0.5){
			angTrukDepan += 2;
			posXTruk -= 1;
		}
		if (angTrukDepan > -0.1){
			belok = 0;
		}
	}
	
	//Belok kiri
	if (belok == 1){
		if (angTrukDepan <= 10){
			angTrukDepan += 2;
		}
		if (angTrukDepan > 9.9){
			belok = 2;
		}
	}
	if (belok >= 2){
		if (angTrukDepan >= 0.5){
			angTrukDepan -= 2;
			posXTruk += 1;
		}
		if (angTrukDepan < 0.1){
			belok = 0;
		}
	}
}

float angTrukBelakang = 0;

void TrukMove2()
{
	if (belok == -1 and angTrukDepan <= -4.9){
		if (angTrukBelakang >= -10){
			angTrukBelakang -= 2;
		}
	}
	if (belok == -2 and angTrukDepan >= -5.1){
		if (angTrukBelakang <= -0.5){
			angTrukBelakang += 2;
		}
	}
	if (belok == 1 and angTrukDepan >= 4.9){
		if (angTrukBelakang <= 10){
			angTrukBelakang += 2;
		}
	}
	if (belok == 2 and angTrukDepan <= 5.1){
		if (angTrukBelakang >= 0.5){
			angTrukBelakang -= 2;
		}
	}
}


float speed = 0;
float posZJalan = -1000;
int ujung = 0;


// Fungsi untuk membuat pohon jenis 1
void Pohon1( int r, int g, int b) {
	glPushMatrix();
		glRotatef(0,0,1,0);
		glTranslatef(-40,0,0);
		glScalef(3,3,3);
		glBegin(GL_QUADS);
		// Batang Pohon
		glColor3ub(248, 144, 32);
		glVertex2f(4,0);
		glVertex2f(3.6,0);
		glVertex2f(3.2,1.5);
		glVertex2f(3.6,1.3);
		
		glVertex2f(4,0);
		glVertex2f(4.6,0);
		glVertex2f(3.9,1.4);
		glVertex2f(3.6,1.3);
		
		glVertex2f(3.6,1.3);
		glVertex2f(3.2,1.5);
		glVertex2f(3.4,3.2);
		glVertex2f(3.6,3);
		
		glVertex2f(3.6,1.3);
		glVertex2f(3.9,1.4);
		glVertex2f(3.9,3.1);
		glVertex2f(3.6,3);
		
		glVertex2f(3.6,3);
		glVertex2f(3.4,3.2);
		glVertex2f(3.9,4.3);
		glVertex2f(4.1,4.4);
		
		glVertex2f(3.6,3);
		glVertex2f(3.9,3.1);
		glVertex2f(4.2,4.3);
		glVertex2f(4.1,4.4);
		
		// Daun Kanan Bawah
		glColor3ub(r, g, b);
		glVertex2f(4.1,4.4);
		glVertex2f(4.5,4.6);
		glVertex2f(4.7,4.4);
		glVertex2f(4.5,4.2);
		
		glVertex2f(4.2,4.3);
		glVertex2f(4.5,4.6);
		glVertex2f(4.7,4.4);
		glVertex2f(4.5,4.2);
		
		glVertex2f(4.1,4.4);
		glVertex2f(4.5,4.6);
		glVertex2f(4.7,4.4);
		glVertex2f(4.2,4.3);
		
		glVertex2f(4.5,4.2);
		glVertex2f(4.7,4.4);
		glVertex2f(5.2,3.7);
		glVertex2f(5,3.5);
			
		glVertex2f(5.1,4.3);
		glVertex2f(4.7,4.4);
		glVertex2f(5.2,3.7);
		glVertex2f(5.4,3.6);
		
		glVertex2f(5.1,4.3);
		glVertex2f(4.7,4.4);
		glVertex2f(4.5,4.6);
		glVertex2f(4.8,4.75);
		
		glVertex2f(5,3.5);
		glVertex2f(5.2,3.7);
		glVertex2f(5.4,3.6);
		glVertex2f(5.2,3);
		
		//// Daun Kiri Bawah
		glVertex2f(3.71,4.88);
		glVertex2f(3.92,4.78);
		glVertex2f(4.1,4.71);
		glVertex2f(3.27,4.32);
		
		glVertex2f(3.32,4.15);
		glVertex2f(4.11,4.42);
		glVertex2f(4.1,4.71);
		glVertex2f(3.27,4.32);
		
		glVertex2f(3.32,4.15);
		glVertex2f(4.11,4.42);
		glVertex2f(3.92,4.26);
		glVertex2f(2.88,3.54);
		
		glVertex2f(3.32,4.15);
		glVertex2f(2.72,3.65);
		glVertex2f(2.89,4.14);
		glVertex2f(3.27,4.32);
		
		glVertex2f(3.32,4.15);
		glVertex2f(2.72,3.65);
		glVertex2f(2.47,3.59);
		glVertex2f(2.89,4.14);
		
		glVertex2f(3.32,4.15);
		glVertex2f(2.88,3.54);
		glVertex2f(2.72,3.65);
		glVertex2f(2.89,4.14);
		
		glVertex2f(2.88,3.54);
		glVertex2f(2.72,3.65);
		glVertex2f(2.47,3.59);
		glVertex2f(2.4,2.8);
		
		// Daun Kanan Tengah
		glVertex2f(4.1,4.4);
		glVertex2f(4.57,4.96);
		glVertex2f(5.18,4.76);
		glVertex2f(4.8,4.65);
		
		glVertex2f(4.64,5.03);
		glVertex2f(4.57,4.96);
		glVertex2f(5.18,4.76);
		glVertex2f(5.1,5.02);
		
		glVertex2f(6.23,5.02);
		glVertex2f(6.17,4.7);
		glVertex2f(5.18,4.76);
		glVertex2f(5.1,5.02);
		
		glVertex2f(6.23,5.02);
		glVertex2f(6.75,4.97);
		glVertex2f(5.83,5.5);
		glVertex2f(5.1,5.02);
		
		glVertex2f(4.64,5.03);
		glVertex2f(4.83,5.27);
		glVertex2f(5.83,5.5);
		glVertex2f(5.1,5.02);
		
		glVertex2f(6.23,5.02);
		glVertex2f(6.17,4.7);
		glVertex2f(7.12,4.34);
		glVertex2f(6.75,4.97);
		
		//// Daun Kiri Tengah
		glVertex2f(3.71,4.88);
		glVertex2f(2.49,4.67);
		glVertex2f(2.14,4.9);
		glVertex2f(2.84,4.94);
		
		glVertex2f(3.71,4.88);
		glVertex2f(2.49,4.67);
		glVertex2f(2.3,4.39);
		glVertex2f(3.27,4.32);
		
		glVertex2f(1.46,4.27);
		glVertex2f(2.49,4.67);
		glVertex2f(2.3,4.39);
		glVertex2f(1.48,3.99);
		
		glVertex2f(1.46,4.27);
		glVertex2f(2.49,4.67);
		glVertex2f(2.14,4.9);
		glVertex2f(1.34,4.35);
		
		glVertex2f(1.46,4.27);
		glVertex2f(1.48,3.99);
		glVertex2f(1.05,3.71);
		glVertex2f(1.34,4.35);
		
		//// Daun Kanan ATAS
		glColor3ub(r-21, g-22, b-23);
		glVertex2f(4.1,4.4);
		glVertex2f(4.1,4.71);
		glVertex2f(4.34,5.3);
		glVertex2f(4.83,5.27);
		
		glVertex2f(4.57,4.96);
		glVertex2f(4.64,5.03);
		glVertex2f(4.83,5.27);
		glVertex2f(4.34,5.3);
		
		glVertex2f(4.78,5.87);
		glVertex2f(5.5,6);
		glVertex2f(4.83,5.27);
		glVertex2f(4.34,5.3);
		
		glVertex2f(4.78,5.87);
		glVertex2f(5.5,6);
		glVertex2f(5.5,6.27);
		glVertex2f(4.85,6.25);
		
		glVertex2f(4.78,5.87);
		glVertex2f(4.85,6.25);
		glVertex2f(5.69,6.48);
		glVertex2f(5.5,6.27);
		
		glVertex2f(5.69,6.48);
		glVertex2f(6.5,6.13);
		glVertex2f(5.5,6);
		glVertex2f(5.5,6.27);
		
		glVertex2f(4.78,5.87);
		glVertex2f(4.85,6.25);
		glVertex2f(4.23,5.71);
		glVertex2f(4.34,5.3);
		
		glVertex2f(4.1,4.4);
		glVertex2f(4.1,4.71);
		glVertex2f(4.23,5.71);
		glVertex2f(4.34,5.3);
		
		//// Daun Tengah Atas
		glVertex2f(4.1,4.71);
		glVertex2f(3.97,5.6);
		glVertex2f(4.17,6);
		glVertex2f(4.23,5.71);
		
		glVertex2f(3.95,6.45);
		glVertex2f(3.97,5.6);
		glVertex2f(4.17,6);
		glVertex2f(4.03,6.61);
		
		glVertex2f(3.95,6.45);
		glVertex2f(3.97,5.6);
		glVertex2f(3.82,5.7);
		glVertex2f(3.8,6.5);
		
		glVertex2f(3.71,4.88);
		glVertex2f(3.97,5.6);
		glVertex2f(3.82,5.7);
		glVertex2f(3.76,5.41);
		
		glVertex2f(3.71,4.88);
		glVertex2f(3.97,5.6);
		glVertex2f(4.1,4.71);
		glVertex2f(3.92,4.78);
		
		glVertex2f(3.95,6.45);
		glVertex2f(3.8,6.5);
		glVertex2f(3.65,7.03);
		glVertex2f(4.03,6.61);
		
		//// Daun Kiri Atas
		glVertex2f(3.82,5.7);
		glVertex2f(3.76,5.41);
		glVertex2f(3.55,5.76);
		glVertex2f(3.5,6.23);
		
		glVertex2f(3.27,6.43);
		glVertex2f(3.25,6.25);
		glVertex2f(3.55,5.76);
		glVertex2f(3.5,6.23);
		
		glVertex2f(3.71,4.88);
		glVertex2f(3.76,5.41);
		glVertex2f(3.55,5.76);
		glVertex2f(3.31,5.84);
		
		glVertex2f(3.12,6.21);
		glVertex2f(3.25,6.25);
		glVertex2f(3.55,5.76);
		glVertex2f(3.31,5.84);
		
		glVertex2f(3.12,6.21);
		glVertex2f(3.25,6.25);
		glVertex2f(3.27,6.43);
		glVertex2f(2.78,6.54);
		
		//// Daun Kiri Tengah Atas
		glVertex2f(3.71,4.88);
		glVertex2f(2.73,5.66);
		glVertex2f(2.75,6.08);
		glVertex2f(3.31,5.84);
		
		glVertex2f(3.71,4.88);
		glVertex2f(2.73,5.66);
		glVertex2f(2.19,5.47);
		glVertex2f(2.84,4.94);
		
		glVertex2f(1.74,5.88);
		glVertex2f(2.73,5.66);
		glVertex2f(2.19,5.47);
		glVertex2f(1.37,5.59);
		
		glVertex2f(1.74,5.88);
		glVertex2f(2.73,5.66);
		glVertex2f(2.75,6.08);
		glVertex2f(1.64,6.18);
		
		glVertex2f(1.74,5.88);
		glVertex2f(1.37,5.59);
		glVertex2f(0.68,5.56);
		glVertex2f(1.64,6.18);
		
		glEnd();
	glPopMatrix();
}

// Fungsi untuk membuat Pohon jenis 2
void Pohon2() {
	glPushMatrix();
		glRotatef(180,0,1,0);
		Pohon1(96, 40, 120);
		glPushMatrix();
		glTranslatef(-29,0,29);
		glRotatef(-90,0,1,0);
		Pohon1(96, 40, 120);
		glTranslatef(92,0,-58);
		glRotatef(-180,0,1,0);
		Pohon1(96, 40, 120);
		glPopMatrix();
	glPopMatrix();

}
void Gedung()
{
	glPushMatrix();
	glRotatef(90,0,1,0);
	glTranslatef(0,0,60);
	glScalef(6,6,6);
	glBegin(GL_QUADS);
		// Bagian Bawah
		glColor3ub(90, 185, 168);
		glVertex2f(1,0);
		glVertex2f(6,0);
		glVertex2f(6,3);
		glVertex2f(1,3);
		
		// Bagian 2
		glVertex2f(1,3);
		glVertex2f(6,3);
		glVertex2f(6,6);
		glVertex2f(1,6);
		
		// Bagian 3
		glVertex2f(1,6);
		glVertex2f(6,6);
		glVertex2f(6,9);
		glVertex2f(1,9);
		
		// Bagian 4
		glVertex2f(1,9);
		glVertex2f(6,9);
		glVertex2f(6,12);
		glVertex2f(1,12);
		
		// Bagian Atas
		glVertex2f(1,12);
		glVertex2f(6,12);
		glVertex2f(6,15);
		glVertex2f(1,15);
		
		// Sela Sela Gedung
		glColor3ub(30, 96, 110);
		glVertex2f(-1,0);
		glVertex2f(1,0);
		glVertex2f(1,15);
		glVertex2f(-1,15);
		
		glVertex2f(8,0);
		glVertex2f(6,0);
		glVertex2f(6,15);
		glVertex2f(8,15);
		
		// Bagian Pintu Masuk
		glColor3ub(196, 240, 194);
		glVertex3f(2,3,-.1);
		glVertex3f(2,2,-.1);
		glVertex3f(5,2,-.1);
		glVertex3f(5,3,-.1);
			// Pintu 1
		glColor3ub(30, 96, 110);
		glVertex3f(2.5,2,-.1);
		glVertex3f(2.5,0,-.1);
		glVertex3f(3.5,0,-.1);
		glVertex3f(3.5,2,-.1);
			// Pintu 2
		glColor3ub(45, 27, 0);
		glVertex3f(4.5,2,-.1);
		glVertex3f(4.5,0,-.1);
		glVertex3f(3.5,0,-.1);
		glVertex3f(3.5,2,-.1);
		
		// Jendela Gedung
		glColor3ub(196, 240, 194);
		glVertex3f(2,6,-.1);
		glVertex3f(2,4,-.1);
		glVertex3f(3,4,-.1);
		glVertex3f(3,6,-.1);
		
		glVertex3f(4,6,-.1);
		glVertex3f(4,4,-.1);
		glVertex3f(5,4,-.1);
		glVertex3f(5,6,-.1);
		
		glVertex3f(2,9,-.1);
		glVertex3f(2,7,-.1);
		glVertex3f(3,7,-.1);
		glVertex3f(3,9,-.1);
		
		glVertex3f(4,9,-.1);
		glVertex3f(4,7,-.1);
		glVertex3f(5,7,-.1);
		glVertex3f(5,9,-.1);
		
		glVertex3f(2,12,-.1);
		glVertex3f(2,15,-.1);
		glVertex3f(3,15,-.1);
		glVertex3f(3,12,-.1);
		
		glVertex3f(4,12,-.1);
		glVertex3f(4,15,-.1);
		glVertex3f(5,15,-.1);
		glVertex3f(5,12,-.1);
	glEnd();
	glPopMatrix();
}
 
float yappari = 15;


float posZPohon = -100;
int ujungP = 0;

void PohonMove()
{
	if(ujungP == 0)
	{
		posZPohon -= speed; //Kecepatan jalan
	} else 
	{
		posZPohon = -100;
		ujungP = 0;
	}
	
	if(posZPohon <= -400) ujungP = 1;
}

float posZGedung = -100;
int ujungG = 0;

void GedungMove(){
	if(ujungG == 0)
	{
		posZGedung -= speed; //Kecepatan jalan
	} else 
	{
		posZGedung = -100;
		ujungG = 0;
	}
	
	if(posZGedung <= -400) ujungG = 1;
}

float posZTembok = 100;
int ujungT = 0;

void Environment()
{
	//Grid bawah
	glPushMatrix();
	 glEnable(GL_LINE_SMOOTH);
	 glColor3ub(100,100,255);
	 glLineWidth(1);
		 glBegin(GL_LINES); 
		 for(i=Z_MIN;i<Z_MAX;i+=gap) 
		 { 
			 glVertex3f(i, 0, Z_MIN); 
			 glVertex3f(i, 0, Z_MAX); 
		 } 
		 for(i=X_MIN;i<X_MAX;i+=gap) 
		 { 
			 glVertex3f(X_MIN, 0, i); 
			 glVertex3f(X_MAX, 0, i); 
		 } 
		 glEnd(); 
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0,0,500);
	glScalef(0.5,0.69,0.7);
		//box depan
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _textureIdDepan);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(100.0f, 0.05f, 100.0f);	
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(100.0f,  135, 100.0f);	
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( -100.0f,  135, 100.0f);	
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-100.0f, 0.05f, 100.0f);	
		glEnd();
		glPopMatrix();
		
		//box kiri
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _textureIdKiri);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(200.0f, 0.05f, 100.0f);	
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(200.0f,  135, 100.0f);	
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 100.0f,  135, 100.0f);	
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(100.0f, 0.05f, 100.0f);	
		glEnd();
		glPopMatrix();
		
		//box kanan
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _textureIdKanan);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(-100.0f, 0.05f, 100.0f);	
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(-100.0f,  135, 100.0f);	
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( -200.0f,  135, 100.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-200.0f, 0.05f, 100.0f);	
		glEnd();
		glPopMatrix();
	glPopMatrix();
	
	//box belakang
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureIdBelakang);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(100.0f, 0.05f, -100.0f);	
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(100.0f,  135, -100.0f);	
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(-100.0f,  135, -100.0f);	
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-100.0f, 0.05f, -100.0f);
	glEnd();
	glPopMatrix();
	
//	//box atas
//	glPushMatrix();
//	glScalef(0.8,0.7,6);
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, _textureIdAtas);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0f, 0.0f); 
//	glVertex3f(-100.0f, 135, -100.0f);	
//	glTexCoord2f(1.0f, 0.0f); 
//	glVertex3f(-100.0f,  135, 100.0f);	
//	glTexCoord2f(1.0f, 1.0f); 
//	glVertex3f(100.0f,  135, 100.0f);	
//	glTexCoord2f(0.0f, 1.0f);
//	glVertex3f(100.0f, 135, -100.0f);	
//	glEnd();
//	glPopMatrix();
	
	    ////////////////////////// LANTAI DI BAWAH GRID ///////////////////////////    
	glPushMatrix();
		 glColor3ub(10,10,10);
		 glBegin(GL_QUADS);
		 glVertex3f(-500.,-0.,-700.);
		 glVertex3f(500.,-0.,-700.);
		 glVertex3f(500.,-0.,700.);
		 glVertex3f(-500.,-0.,700.);
		 glEnd();
	glPopMatrix(); 
}



void Jalan() {
	glPushMatrix(); //Bagian kepala
		panjang = 50;
		lebar = 50;
		tinggi = 0.5;
		glTranslatef(0,0,5);
		glColor3f(0.1f,0.1f,0.1f);
		//depan 
		glPushMatrix(); 
		glTranslatef(0,0,panjang/2);
		glBegin(GL_QUADS); 
		glVertex3f(-lebar/2,0.0f,0.0f); 
		glVertex3f(lebar/2,0.0f,0.0f); 
		glVertex3f(lebar/2,tinggi,0.0f); 
		glVertex3f(-lebar/2,tinggi,0.0f); 
		glEnd(); 
		glPopMatrix(); 
		// atas 
		glPushMatrix(); 
		glRotated(-90, 1, 0, 0); 
		glTranslatef(0,0,tinggi); 
		glBegin(GL_QUADS); 
		glVertex3f(-lebar/2,-panjang/2,0.0f); 
		glVertex3f(lebar/2,-panjang/2,0.0f); 
		glVertex3f(lebar/2,panjang/2,0.0f); 
		glVertex3f(-lebar/2,panjang/2,0.0f); 
		glEnd(); 
		glPopMatrix(); 
		// belakang 
		glPushMatrix(); 
		glRotated(-180, 1, 0, 0);
		glTranslatef(0,0,panjang/2); 
		glBegin(GL_QUADS); 
		glTexCoord2f(0.0f,0.0f); // kiri bawah 
		glVertex3f(-lebar/2,-tinggi,0.0f); 
		glTexCoord2f(1.0f,0.0f); // kanan bawah 
		glVertex3f(lebar/2,-tinggi,0.0f); 
		glTexCoord2f(1.0f,1.0f); // kanan atas 
		glVertex3f(lebar/2,0.0f,0.0f); 
		glTexCoord2f(0.0f,1.0f); // kanan bawah 
		glVertex3f(-lebar/2,0.0f,0.0f); 
		glEnd(); 
		glPopMatrix(); 
		// bawah 
		glPushMatrix(); 
		glRotated(90, 1, 0, 0); 
		glTranslatef(0,0,0); 
		glBegin(GL_QUADS); 
		glTexCoord2f(0.0f,0.0f); // kiri bawah 
		glVertex3f(-lebar/2,-panjang/2,0.0f); 
		glTexCoord2f(1.0f,0.0f); // kanan bawah 
		glVertex3f(lebar/2,-panjang/2,0.0f); 
		glTexCoord2f(1.0f,1.0f); // kanan atas 
		glVertex3f(lebar/2,panjang/2,0.0f); 
		glTexCoord2f(0.0f,1.0f); // kanan bawah 
		glVertex3f(-lebar/2,panjang/2,0.0f); 
		glEnd(); 
		glPopMatrix(); 
		// kiri 
		glPushMatrix(); 
		glRotated(-90, 0, 1, 0); 
		glTranslatef(0,0,lebar/2); 
		glBegin(GL_QUADS); 
		glVertex3f(-panjang/2,0.0f,0.0f); 
		glVertex3f(panjang/2,0.0f,0.0f); 
		glVertex3f(panjang/2,tinggi,0.0f); 
		glVertex3f(-panjang/2,tinggi,0.0f); 
		glEnd();
		glPopMatrix(); 
		// kanan 
		glPushMatrix(); 
		glRotated(90, 0, 1, 0); 
		glTranslatef(0,0,lebar/2); 
		glBegin(GL_QUADS); 
		glVertex3f(-panjang/2,0.0f,0.0f); 
		glVertex3f(panjang/2,0.0f,0.0f); 
		glVertex3f(panjang/2,tinggi,0.0f); 
		glVertex3f(-panjang/2,tinggi,0.0f); 
		glEnd(); 
		glPopMatrix();
 	glPopMatrix();
 	
 	glPushMatrix(); 
		panjang = 6;
		lebar = 1;
		tinggi = 4;
		glRotated(-90,1,0,0);
		glTranslatef(0,-7.5,-2.29);
		glColor3f(1,1,1);
		//depan 
		glPushMatrix(); 
		glTranslatef(0,0,panjang/2);
		glBegin(GL_QUADS); 
		glVertex3f(-lebar/2,0.0f,0.0f); 
		glVertex3f(lebar/2,0.0f,0.0f); 
		glVertex3f(lebar/2,tinggi,0.0f); 
		glVertex3f(-lebar/2,tinggi,0.0f); 
		glEnd(); 
		glPopMatrix();
 	glPopMatrix();
}

// Fungsi untuk membuat TEMBOK
void Tembok() {
	glPushMatrix();
	glColor3ub(100,100,100);
		glPushMatrix();
		glTranslatef(5, 0, 70);
		glScalef(3, 8, 1);
		glutSolidCube(3);
		glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glScalef(0.75,1.5,1);
	glTranslatef(7.7,0,68.4);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(-8,0);
	glTexCoord2f(1,0);
	glVertex2f(5,0);
	glTexCoord2f(1,1);
	glVertex2f(5,8);
	glTexCoord2f(0,1);
	glVertex2f(-8,8);
	glEnd();
	glPopMatrix();
}



//Start////////////////////////////



void PergerakanJalan()
{
	//jika jalan belom mencapai ujung
	if(ujung == 0)
	{
		posZJalan -= speed; //Kecepatan jalan
	} else 
	{
		posZJalan = -100;
		ujung = 0;
	}
	
	if(posZJalan <= -400) {
		ujung = 1;
	}
	if(speed >= 10){
		speed = 9;
	}
}

void TembokMove(){
	if(ujungT == 0)
	{
		posZTembok -= speed; //Kecepatan jalan
	} else 
	{
		posZTembok = 100;
		ujungT = 0;
	}
	
	if(posZTembok <= -400) ujungT = 1;
}

bool touch = false;

void isTouch(){
	if ((posZTruk < posZTembok+80 and posZTruk > posZTembok +64) and (posXTruk >= -8 and posXTruk <= 5)){
		touch = true;
	}
}

void Object()
{		
	glPushMatrix();
		glPushMatrix();
			TrukMove();
			glRotatef(angTrukDepan,0,1,0);
			glTranslatef(posXTruk,0, posZTruk);
			TrukDepan();
		glPopMatrix();
		glPushMatrix();
			TrukMove2();
			glRotatef(angTrukBelakang,0,1,0);
			glTranslatef(posXTruk,0, posZTruk);
			TrukBelakang();
		glPopMatrix();
	glPopMatrix();
	
	
	glPushMatrix();
	int a;	
	PergerakanJalan();
	for(a = 180; a > 0; a -= 1){
		glPushMatrix();
			glTranslatef(-4,0,posZJalan+(a*5));
			Jalan();
		glPopMatrix();
	}
	glPopMatrix();
	
	glPushMatrix();
	int b;	
	PohonMove();
	for(b = 20; b > 0; b -= 1){
		glPushMatrix();
			glTranslatef(-4,0,posZPohon+(b*50));
			Pohon1(96, 40, 120);
			Pohon2();
			Gedung();
			glPushMatrix();
			glTranslatef(0,0,-100);
			glRotated(180,0,1,0);
			Gedung();
			glPopMatrix();
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
		TembokMove();
		glTranslatef(-4,0,posZTembok);
		Tembok();
		glPushMatrix();
		glTranslatef(-15,0,0);
		Tembok();
		glPopMatrix();
	glPopMatrix();
}


void drawStrokeText2(char* str,int x,int y,int z)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y+8,z);
	  glScalef(0.05f,0.05f,0.02f);

	  for (c=str; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN , *c);
	  }
	  glPopMatrix();
}

void display() { 
	// Kalau move dan angle tidak nol, gerakkan kamera... 
 	if (deltaMove) 
 		moveMeFlat(deltaMove); 
 		if (deltaAngle) { 
 			angle += deltaAngle; 
 			orientMe(angle); 
 		} 
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glPushMatrix();
	glRotated(rotAngleX+10, 1, 0, 0);
 	glRotated(rotAngleY, 0, 1, 0);
 	glRotated(rotAngleZ, 0, 0, 1);
	isTouch();
	if (touch){
		TrukDepan();
		TrukBelakang();
		drawStrokeText2("Game Over",-23,3,0);
		glRotated(180,0,1,0);
		drawStrokeText2("Game Over",-23,10,0);
		rotAngleY-=1;
		 glClearColor(1,1,1,1);
	} else {
	 	Environment();
	 	Object();
	 	 glClearColor(0,0,0,1);
	}
 	glPopMatrix();
 	glFlush(); 
 	glutSwapBuffers(); 
}
 
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'a':
			belok++; break;
		case 'd':
			belok--; break;
		case 'w':
			posZTruk++; speed++; break;
		case 's':
			posZTruk--; speed--; break;
		case 'i':
			rotAngleX -= 10; break;
		case 'k':
			rotAngleX += 10; break;
		case 'j':
			rotAngleY -= 10; break;
		case 'l':
			rotAngleY += 10; break;
		case 27:
			exit(0);
		default:
			break;
	} glutPostRedisplay();
}

GLUquadricObj *IDquadric;
// Variable untuk pencahayaan  
const GLfloat light_ambient[] = { .89f, .89f, .89f, 1.0f }; 
const GLfloat light_diffuse[] = { .5f, .5f, .5f, 1.0f }; 
const GLfloat light_specular[] = { .2f, .2f, .2f, 1.0f }; 
const GLfloat light_position[] = { 50.0f, 30.0f, 0.0f, 1.0f }; 
const GLfloat mat_ambient[] = { .7f, .7f, .7f, 1.0f }; 
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; 
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat high_shininess[] = { 100.0f }; 

void lighting(){ 
 // Fungsi mengaktifkan pencahayaan 
 glEnable(GL_DEPTH_TEST); 
 glDepthFunc(GL_LESS); 
 glEnable(GL_LIGHT0); 
 glEnable(GL_NORMALIZE); 
 glEnable(GL_COLOR_MATERIAL); 
 glEnable(GL_LIGHTING); 
 glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); 
 glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); 
 glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); 
 glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
 glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); 
 glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); 
}
 
void init(void) 
{ 
 	glEnable (GL_DEPTH_TEST); 
 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
 	IDquadric=gluNewQuadric();      // Create A Pointer To The Quadric Object ( NEW )
  	gluQuadricNormals(IDquadric, GLU_SMOOTH);  // Create Smooth Normals ( NEW )
  	gluQuadricTexture(IDquadric, GL_TRUE);    // Create Texture Coords ( NEW )
  	Image* imagetembok = loadBMP("tembok.bmp");
  	Image* imagekanan = loadBMP("kiri.bmp");
  	Image* imagekiri = loadBMP("kanan.bmp");
  	Image* imagebelakang = loadBMP("belakang.bmp");
  	Image* imagedepan = loadBMP("depan.bmp");
  	Image* imageatas = loadBMP("atas.bmp");
	_textureId = loadTexture(imagetembok);
	_textureIdDepan = loadTexture(imagedepan);
	_textureIdKanan = loadTexture(imagekanan);
	_textureIdBelakang = loadTexture(imagebelakang);
	_textureIdKiri = loadTexture(imagekiri);
	_textureIdAtas = loadTexture(imageatas);
	delete imagetembok;
	delete imagedepan;
	delete imagekanan;
	delete imagebelakang;
	delete imagekiri;
	delete imageatas;
} 

int main(int argc, char **argv) 
{ 
 glutInit(&argc, argv); 
 glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
 glutInitWindowPosition(300,100); 
 glutInitWindowSize(800,600); 
 glutCreateWindow("Cybertruck"); 
 glutSpecialFunc(pressKey);
 glutSpecialUpFunc(releaseKey);
 glutDisplayFunc(display); 
 glutKeyboardFunc(keyboard);
 glutIdleFunc(display); // Fungsi display-nya dipanggil terusmenerus 
 glutReshapeFunc(Reshape); 
 lighting(); 
 init(); 
 glutMainLoop(); 
 return(0); 
}
