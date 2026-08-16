#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;
#define SCREEN_HEIGHT 480    //screen size is considered as 640 x 480


struct POINT2D
{
    float x;
    float y;
};

POINT2D ptArr[5];
int i=0;
int j=0;


//to alter the coordinates range
void init()
{
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}


void drawPointsCircle()
{
    glColor3f(1, 0, 0);
    glPointSize(5);

    glBegin(GL_POINTS);
        for (int k = 0; k < 2; ++k)
        {
            glVertex2f(ptArr[k].x, ptArr[k].y);
        }
    glEnd();
}

void drawCircle()
{
        int A = ptArr[0].x;
        int B = ptArr[0].y;
        int px = ptArr[1].x;
        int py = ptArr[1].y;

        float R = sqrt(pow((A-px),2) + pow((B-py),2));

        glColor3f(0, 0, 1);
        glBegin(GL_LINE_LOOP);
            for (float t=0; t<=2*M_PI; t+=0.1)
            {
               float xval = A + R*cos(t);
               float yval = B + R*sin(t);
               glVertex2f(xval, yval);
            }
        glEnd();
}



void drawPointsEllipse()
{
    glColor3f(1, 0, 0);
    glPointSize(5);

    glBegin(GL_POINTS);
        for (int k = 0; k < 3; k++)
        {
            glVertex2f(ptArr[k].x, ptArr[k].y);
        }
    glEnd();
}

void drawEllipse()
{
    int X = ptArr[0].x;
    int Y = ptArr[0].y;
    int ax = ptArr[1].x;
    int ay = ptArr[1].y;
    int bx = ptArr[2].x;
    int by = ptArr[2].y;

    float A = sqrt(pow((X-ax),2) + pow((Y-ay),2));
    float B = sqrt(pow((X-bx),2) + pow((Y-by),2));

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
        for (float t=0; t<=2*M_PI; t+=0.1)
        {
           float xval = X + A*cos(t);
           float yval = Y + B*sin(t);
           glVertex2f(xval, yval);
        }
    glEnd();
}







void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawPointsEllipse();
    if (i==0)
        drawEllipse();

    /* drawPointsCircle();
    if (i==0)
    {
        drawCircle();
    } */
    glFlush();
}


void mouse(int button, int state, int x, int y)
{
    glColor3f(1,0,0);
    glPointSize(3);
    cout <<i <<endl;
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        ptArr[i].x = x;
        ptArr[i++].y = SCREEN_HEIGHT - y;
        cout <<"Current position: " <<x <<" " <<y <<endl;
        glBegin(GL_POINTS);
            glVertex2f(x, SCREEN_HEIGHT-y);
        glEnd();
        glFlush();


        /* // for circle --> 2 points
        if (i==2)
        {
            cout <<"drawing circle" <<endl;
            i=0;
            glutPostRedisplay();
        } */



        /* // for ellipse --> 3 points
        if (i==3)
        {
            cout <<"drawing ellipse" <<endl;
            i=0;
            glutPostRedisplay();
        } */
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(80,80);
    glutInitWindowSize(640,480);
    glutCreateWindow("drawing");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
}
