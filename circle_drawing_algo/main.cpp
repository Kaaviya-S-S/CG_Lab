#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define SCREEN_HEIGHT 480

struct POINT2D
{
    float x;
    float y;
};
POINT2D ptArr[5];
int i = 0;


void init()
{
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}


void showEndPoints()
{
    glColor3f(1, 0, 0);

    glBegin(GL_POINTS);
        for (int k = 0; k < 2; ++k)
        {
            glVertex2f(ptArr[k].x, ptArr[k].y);
        }
    glEnd();
}


void plot_Circle_Coordinates(float x_k, float y_k, float xc, float yc)
{
    glBegin(GL_POINTS);
        glColor3f(0,0,0);     glVertex2f(xc + ( x_k), yc + ( y_k));
        glColor3f(0,1,0);     glVertex2f(xc + (-x_k), yc + ( y_k));
        glColor3f(0,0,1);     glVertex2f(xc + (-x_k), yc + (-y_k));
        glColor3f(0,1,1);     glVertex2f(xc + ( x_k), yc + (-y_k));
        glColor3f(1,0,0);     glVertex2f(xc + ( y_k), yc + ( x_k));
        glColor3f(1,1,0);     glVertex2f(xc + (-y_k), yc + ( x_k));
        glColor3f(1,0,1);     glVertex2f(xc + (-y_k), yc + (-x_k));
        glColor3f(0.4,0,0.8); glVertex2f(xc + ( y_k), yc + (-x_k));
    glEnd();
}


void midpoint_circle_algorithm()
{
    //circle center
    float xc = ptArr[0].x;
    float yc = ptArr[0].y;

    //radius
    float r = sqrt(pow((ptArr[1].x - xc),2) + pow((ptArr[1].y - yc),2));

    float x_k = 0;
    float y_k = r;
    float p_k = 1 - r;

    glBegin(GL_POINTS);
        glColor3f(1,0,0); glVertex2f(xc+x_k, yc+y_k);  // initial point (0,r)
    glEnd();
    while(x_k < y_k)
    {
        if(p_k < 0)
        {
            x_k += 1;
            p_k += 2*(x_k) + 1;
        }
        else
        {
            x_k += 1;
            y_k -= 1;
            p_k += 2*(x_k) - 2*(y_k) + 1;
        }
         plot_Circle_Coordinates(x_k, y_k, xc, yc);  //point the current point and other 7 points
    }
    glFlush();
}



void parametric_circle_equation()
{
    int A = ptArr[0].x;
    int B = ptArr[0].y;
    int px = ptArr[1].x;
    int py = ptArr[1].y;

    float R = sqrt(pow((A-px),2) + pow((B-py),2));

    glColor3f(0, 0, 1);
    glBegin(GL_POINTS);
        for (float t=0; t<=2*M_PI; t+=0.01)
        {
           float xval = A + R*cos(t);
           float yval = B + R*sin(t);
           glVertex2f(xval, yval);
        }
    glEnd();
}



void standard_circle_equation()
{
    int A = ptArr[0].x;
    int B = ptArr[0].y;
    int px = ptArr[1].x;
    int py = ptArr[1].y;

    float R = sqrt(pow((A-px),2) + pow((B-py),2));

    glColor3f(0, 0, 1);
    glBegin(GL_POINTS);
        for (float x = A - R; x <= A + R; x += 0.1)
        {
            float y1 = B + sqrt(R*R - (x - A)*(x - A));
            float y2 = B - sqrt(R*R - (x - A)*(x - A));

            glVertex2f(x, y1);
            glVertex2f(x, y2);
        }
    glEnd();
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    showEndPoints();
    if(i==0)
    {
        //standard_circle_equation();
        //parametric_circle_equation();
        midpoint_circle_algorithm();
    }
    glFlush();
}



void mouse(int button, int state, int x, int y)
{
    glColor3f(1,0,0);

    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        ptArr[i].x = x;
        ptArr[i++].y = SCREEN_HEIGHT - y;
        cout <<"Current position: " <<x <<" " <<SCREEN_HEIGHT - y <<endl;
        glBegin(GL_POINTS);
            glVertex2f(x, SCREEN_HEIGHT-y);
        glEnd();
        glFlush();

        if (i==2)
        {
            cout <<"draw circle" <<endl;
            i=0;
            glutPostRedisplay();
        }
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("line drawing algo");

    init();
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
