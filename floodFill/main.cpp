#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
using namespace std;
#define SCREEN_HEIGHT 480	//screen size is considered as 640 x 480


struct POINT2D
{
   float x;
   float y;
};
POINT2D ptArr[50];
int i=0;

float fillColor[3] = {1.0f, 0.0f, 0.0f};    	//red color
float interiorColor[3] = {1.0f, 1.0f, 1.0f};	//white - default bg color
bool polygon = false;


//to alter the coordinates range
void init()
{
   glClearColor(1, 1, 1, 0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,640,0,480);
}


void setPixel(int x, int y)
{
   glColor3f(fillColor[0], fillColor[1], fillColor[2]);
   glBegin(GL_POINTS);
   	glVertex2f(x,y);
   glEnd();
   glFlush();
}


void floodFill(int x, int y)
{
   float Color[3];

   // glReadPixels(xpos, ypos, width, height, format, type, return_data)
   glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, Color);


   if((Color[0]==interiorColor[0] && Color[1]==interiorColor[1] && Color[2]==interiorColor[2]) 	//pixel color is interior color (not colored/ bg color)
   && (Color[0]!=fillColor[0] || Color[1]!=fillColor[1] || Color[2]!=fillColor[2]))            	// pixel is not already colored
   {
   	setPixel(x,y);
   	floodFill(x+1, y);
   	floodFill(x-1, y);
   	floodFill(x, y+1);
   	floodFill(x, y-1);
   }
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	/*
	glColor3f(0,0,0);
	if(polygon)
	{
    	glBegin(GL_LINE_LOOP);
        	for (int j = 0; j<i; j++)
        	{
            	glVertex2f(ptArr[j].x, ptArr[j].y);
        	}
    	glEnd();
	}
    */

	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
    	glVertex2f(100,100);
    	glVertex2f(100,200);
    	glVertex2f(200,200);
    	glVertex2f(200,100);
	glEnd();

	glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);
    	glVertex2f(200,100);
    	glVertex2f(300,100);
    	glVertex2f(300,50);
    	glVertex2f(200,50);
	glEnd();

	glColor3f(0,0,1);
	glBegin(GL_LINE_LOOP);
    	glVertex2f(300,100);
    	glVertex2f(300,150);
    	glVertex2f(350,200);
	glEnd();

	glColor3f(1,1,0);
	glBegin(GL_LINE_LOOP);
    	glVertex2f(200,200);
    	glVertex2f(350,200);
	glEnd();

	glFlush();
}


void mouse(int button, int state, int x, int y)
{
	glColor3f(0,0,0);
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
    	ptArr[i].x = x;
    	ptArr[i++].y = SCREEN_HEIGHT - y;
    	cout <<"Current position: " <<x <<" " <<SCREEN_HEIGHT - y <<endl;
    	glBegin(GL_POINTS);
        	glVertex2f(x, SCREEN_HEIGHT-y);
    	glEnd();
    	glFlush();
	}

	else if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)	//after clicking
	{
   	cout <<"filling start position: " <<x <<" " <<SCREEN_HEIGHT-y <<endl;

   	cout <<fillColor[0] <<" " <<fillColor[1] <<" " <<fillColor[2] <<endl <<endl;

   	floodFill(x, SCREEN_HEIGHT-y);
   	cout <<"done" <<endl;
   	glFlush();
   }
}


void keyboard(unsigned char key, int x, int y)
{
	if(key == 13)  // ASCII code for Enter key
	{
    	cout <<"Draw polygon.." <<endl;
    	polygon = true;
    	glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(80,80);
   glutInitWindowSize(640,480);
   glutCreateWindow("floodFill algo");

   init();
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
}
