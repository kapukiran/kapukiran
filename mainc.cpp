//
//hasan KAPUKIRAN
//040080196
#include<windows.h>
#include <stdio.h>
#include <GL/gl.h> 
#include <GL/glu.h>
#include <GL/glut.h>
#include<math.h>
#include "imageloader.h"

#define PI 3.14159265

static void DrawBox();

GLenum doubleBuffer;
GLUquadricObj *sphere = NULL;

float _angle = 0;
GLuint _textureId;
float angle=50;
float angle1=0;
float angle2=30;
float distance =0.8;
float aaa;
static void Init(){
	// Background Color
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Draw Lines (Wireframe)
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	
}


GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}


static void Draw(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	DrawBox(); 
		
	glutSwapBuffers();
}
static void Key(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
	}
}

static void timerCallback (int value)
{
	// Do timer processing
	angle+=5;
	
	// call back again after 10ms have passed
	glutTimerFunc(2, timerCallback, value);
	// Re-draw
	glutPostRedisplay();
	
}

static void timerCallback1 (int value)
{
	// Do timer processing
	angle1+=1;
	
	// call back again after 10ms have passed
	glutTimerFunc(80, timerCallback1, value);
	// Re-draw
	glutPostRedisplay();
}

static void timerCallback2 (int value)
{
	// Do timer processing
	angle2+=1;
	
	// call back again after 10ms have passed
	glutTimerFunc(40, timerCallback2, value);
	// Re-draw
	glutPostRedisplay();
}


void setLight(){
    GLfloat light_position[] = { 0.0, -1.0, -3, 1.0 };
    GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 0.0, 1.0 };
    
   
    glEnable(GL_LIGHT1);
	 glEnable(GL_LIGHTING);
	 glEnable(GL_CULL_FACE);

// arka yüzeyleri sakla
glCullFace(GL_BACK);

// ýþýk ve rengin çalýþmasý için gerekli

glEnable(GL_COLOR_MATERIAL);  
glEnable(GL_NORMALIZE);
// gouraud tipi ýþýklandýrma

glShadeModel(GL_SMOOTH);
    
  // glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);

    
  // GLfloat global_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    
 //   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
     
    glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
 GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat material_emission[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat material_shininess[] = { 0 };
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    
    glShadeModel(GL_SMOOTH);
}





int main (int argc, char ** argv)
{

	GLenum type;
	int width,height;
	double range;
	glutInit(&argc, argv);

	type = GLUT_RGB;
	type |= GLUT_DOUBLE;

	width=glutGet(GLUT_SCREEN_WIDTH);
	height=glutGet(GLUT_SCREEN_HEIGHT);
	
	glutInitWindowPosition(width*0.25,height*0.25);
	glutInitWindowSize(width*.8,height*.8);
	glutInitDisplayMode( type );
	glutCreateWindow("Proje-1");
	 
	glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE); 
	glEnable(GL_TEXTURE_2D);

    Init();
	range=2;
	glMatrixMode(GL_PROJECTION);
	gluPerspective(70,(double)width/height,1,10);
	
	glMatrixMode(GL_MODELVIEW);

	setLight();
	glutKeyboardFunc(Key);
	glutDisplayFunc(Draw);
	timerCallback(0);
	timerCallback1(0);
	timerCallback1(2);
	glutMainLoop();
	return 0; 
}


static void DrawBox(){
	int i;




	glPushMatrix();
	  glTranslatef(0,-1,-3);
	glPushMatrix();
	
	glRotatef(angle, 0, 1, 0);
	//glColor3f(1, 1, 0);

	Image* img = loadBMP("günes.bmp");
	_textureId = loadTexture(img);
	delete img;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	gluSphere(sphere, 0.5, 20, 20);


	glPopMatrix();
	glPushMatrix();

	glColor3f(0.5,0.5,0.5);
glPointSize(1.0);
glBegin(GL_POINTS); 
for(i = 1; i < 360; i++) {
 float   x = distance * sin(((float)i) * 3.14 / 180);
  float  z = distance * cos(((float)i) * 3.14 / 180);
 glVertex3f(x,0,z); 
}
glEnd();

		glPopMatrix();
	glPushMatrix();

	glTranslatef(distance*(cos(-angle1*PI/180)),0.0,distance*(sin(-angle1*PI/180)));
	glPushMatrix();
	glRotatef(10*angle1, 0, 1, 0);


		Image* img1 = loadBMP("earth.bmp");
	_textureId = loadTexture(img1);
	delete img1;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	gluSphere(sphere, 0.2, 20, 20);




	glPopMatrix();
	glPushMatrix();

		glColor3f(0.5,0.5,0.5);
glPointSize(1.0);
glBegin(GL_POINTS); 
for(i = 1; i < 360; i++) {
 float   x = 0.3 * sin(((float)i) * 3.14 / 180);
  float  z = 0.3 * cos(((float)i) * 3.14 / 180);
 glVertex3f(x,0,z); 
}
glEnd();

		glPopMatrix();


	
	glTranslatef(0.3*(cos(-angle*PI/180)),0.0,0.3*(sin(-angle*PI/180)));
	//glColor3f(0, 1, 0);

	Image* img2 = loadBMP("moon.bmp");
	_textureId = loadTexture(img2);
	delete img2;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	
	glRotatef(30*angle1, 0, 1, 0);
	gluSphere(sphere, 0.05, 20, 20);


   //glutSolidSphere(0.05,20,20);

	glPopMatrix();
	glPushMatrix();

			glColor3f(0.5,0.5,0.5);
glPointSize(1.0);
glBegin(GL_POINTS); 
for(i = 1; i < 360; i++) {
 float   x = 2 * sin(((float)i) * 3.14 / 180);
  float  z = 2 * cos(((float)i) * 3.14 / 180);
 glVertex3f(x,0,z); 
}
glEnd();

   glPopMatrix();

	glTranslatef(2*(cos(angle1*PI/180)),0.0,2*(sin(angle1*PI/180)));
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);
	// glColor3f(1, 0, 0);
	
	 Image* img3 = loadBMP("venus.bmp");
	_textureId = loadTexture(img3);
	delete img3;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	
	glRotatef(30*angle1, 0, 1, 0);
	gluSphere(sphere, 0.05, 20, 20);
	 
	// glutSolidSphere(0.05,20,20);
    

	glPopMatrix();
	glPushMatrix();


	glColor3f(0.5,0.5,0.5);
glPointSize(1.0);
glBegin(GL_POINTS); 
for(i = 1; i < 360; i++) {
 float   x = 0.3 * sin(((float)i) * 3.14 / 180);
  float  z = 0.3 * cos(((float)i) * 3.14 / 180);
 glVertex3f(x,0,z); 
}
glEnd();

   glPopMatrix();
   glPushMatrix();



	glTranslatef(0.3*(cos(-angle*PI/180)),0.0,0.3*(sin(-angle*PI/180)));
	glRotatef(10*angle1, 0, 1, 0);
	// glColor3f(1, 1, 0);
	 Image* img4 = loadBMP("mars.bmp");
	_textureId = loadTexture(img4);
	delete img4;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	
	glRotatef(30*angle1, 0, 1, 0);
	gluSphere(sphere, 0.05, 20, 20);




	
	glPopMatrix();
	glPushMatrix();


	glColor3f(0.5,0.5,0.5);
glPointSize(1.0);
glBegin(GL_POINTS); 
for(i = 1; i < 360; i++) {
 float   x = 0.5 * sin(((float)i) * 3.14 / 180);
  float  z = 0.5 * cos(((float)i) * 3.14 / 180);
 glVertex3f(x,0,z); 
}
glEnd();

   glPopMatrix();

	glTranslatef(0.5*(cos(angle*PI/180)),0.0,0.5*(sin(angle*PI/180)));
	glRotatef(10*angle1, 0, 1, 0);
	 glColor3f(1, 0.9, 0);


	glutSolidSphere(0.03,20,20);
	
	glPopMatrix();


glPopMatrix();

}

