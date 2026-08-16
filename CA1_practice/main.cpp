/*#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#define SCREEN_HEIGHT 480

using namespace std;

struct POINT2D
{
    float x;
    float y;
};
POINT2D ptArr[50];
int i=0;

void init()
{
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}


void DDA_algo()
{
    float del_x = ptArr[1].x - ptArr[0].x;
    float del_y = ptArr[1].y - ptArr[0].y;
    int steps = 0;
    if(abs(del_x) > abs(del_y))
        steps = abs(del_x);
    else
        steps = abs(del_y);

    float x_incr = del_x/(float)steps;
    float y_incr = del_y/(float)steps;

    float xk = ptArr[0].x;
    float yk = ptArr[0].y;
    glBegin(GL_POINTS);
        for(int s=0; s<steps; s++)
        {
            glVertex2f(round(xk),round(yk));
            xk += x_incr;
            yk += y_incr;
        }
    glEnd();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,0,0);

    glBegin(GL_POINTS);
        for(int j=0; j<i; j++)
        {
            glVertex2f(ptArr[j].x, ptArr[j].y);
        }
    glEnd();

    if (i==0)
    {
        //DDA_algo();
        bresenhams_algo();
    }
    glFlush();
}


void mouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
       ptArr[i].x = x;
       ptArr[i++].y = SCREEN_HEIGHT - y;

       cout <<"curr point: " <<x <<" " <<SCREEN_HEIGHT-y <<endl;

       if(i==2)
       {
            cout <<"Draw line.." <<endl;
            i=0;
       }
       glutPostRedisplay();
    }
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(80,80);

    glutCreateWindow("drawing");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    //glutKeyboardFunc(key);
    glutMainLoop();
}
*/
//**************************************************************
/*
// polygon clipping

#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#define SCREEN_HEIGHT 480

using namespace std;

struct POINT2D
{
    float x;
    float y;
};
POINT2D ptArr[50];
POINT2D ptArrClipped[50];
POINT2D ptArrTemp[50];
int i=0;
int k=0;   //for clipped

bool clipped = false;
bool window = false;
bool polygon = false;
int xw_min, yw_min, xw_max, yw_max;

void init()
{
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
        for(int j=0; j<i; j++)
        {
            glVertex2f(ptArr[j].x, ptArr[j].y);
        }
    glEnd();

    if(window)
    {

    	glBegin(GL_POINTS);
        	for (int j=0; j<i; j++)
        	{
            	glVertex2f(ptArr[j].x, ptArr[j].y);
        	}
    	glEnd();

    	glBegin(GL_LINE_LOOP);
        	glVertex2f(xw_min, yw_min);
        	glVertex2f(xw_min, yw_max);
        	glVertex2f(xw_max, yw_max);
        	glVertex2f(xw_max, yw_min);
    	glEnd();

    	if(polygon)
    	{
        	glColor3f(1,1,0);
        	glBegin(GL_POLYGON);
            	for (int j = 0; j<i; j++)
            	{
                	glVertex2f(ptArr[j].x, ptArr[j].y);
            	}
        	glEnd();
    	}

    	if(clipped)
    	{
        	glColor3f(0,1,0);
        	glBegin(GL_POLYGON);
            	for (int j=0; j<k; j++)
            	{
                	glVertex2f(ptArrClipped[j].x, ptArrClipped[j].y);
            	}
        	glEnd();
    	}

    }

    glFlush();
}


void sutherland_hodgeman_algo()
{
    int t=0; //iter var for temp arr
    for (int j=0; j<i; j++)
    {
        ptArrTemp[t++] = ptArr[j];
    }

	char pos;
	char bounds[4] = {'l','b','r','t'};

	for(int z=0; z<4; z++)
    {
        char boundary = bounds[z];
        // complete the code
    }
}


void mouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
       ptArr[i].x = x;
       ptArr[i++].y = SCREEN_HEIGHT - y;
       cout <<"curr point: " <<x <<" " <<SCREEN_HEIGHT-y <<endl;
       glutPostRedisplay();
    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
       if(i>=2 && !window)
       {
        	xw_min = ptArr[0].x;
        	yw_min = ptArr[0].y;
        	xw_max = ptArr[1].x;
        	yw_max = ptArr[1].y;
        	window = true;
        	i = 0;
       }
       glutPostRedisplay();
    }
}


void keyboard(unsigned char key, int x, int y)
{
    if(key==32)  //spacebar
    {
        cout <<"draw polygon!" <<endl;
        polygon = true;
        glutPostRedisplay();
    }
    if (key==13)
    {
        cout <<"clip polygon.." <<endl;
        sutherland_hodgeman_algo();
        clipped = true;
        glutPostRedisplay();
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(80,80);

    glutCreateWindow("drawing");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
*/
//**************************************************************


