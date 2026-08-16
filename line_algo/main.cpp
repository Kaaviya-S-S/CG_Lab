#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

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



void DDA_algorithm()
{
    float del_x = (ptArr[1].x - ptArr[0].x);
    float del_y = (ptArr[1].y - ptArr[0].y);
    int steps = 0;

    if(abs(del_x) > abs(del_y)) {
        steps = abs(del_x);
    }
    else {
        steps = abs(del_y);
    }

    float x_incr = del_x/(float)steps;
    float y_incr = del_y/(float)steps;

    glColor3f(0,0,0);

    glBegin(GL_POINTS);
        float x_k = ptArr[0].x;
        float y_k = ptArr[0].y;
        for(int s=0; s<steps; s++)
        {
            glVertex2f(round(x_k), round(y_k));
            x_k = x_k + x_incr;
            y_k = y_k + y_incr;
        }
    glEnd();
}


/*
void Bresenhams_algorithm()
{
    int del_x = (ptArr[1].x - ptArr[0].x);
    int del_y = (ptArr[1].y - ptArr[0].y);

    glColor3f(0,0,0);
    float x_k = ptArr[0].x;
    float y_k = ptArr[0].y;
    int p_k = 2*del_y - del_x;

    glBegin(GL_POINTS);
        for(int s=0; s<del_x-1; s++)
        {
            glVertex2f(x_k, y_k);

            if(p_k < 0)
            {
                x_k = x_k + 1;
                p_k = p_k + 2*del_y;
            }
            else
            {
                x_k = x_k + 1;
                y_k = y_k + 1;
                p_k = p_k + 2*del_y - 2*del_x;
            }
        }
    glEnd();
}
*/

void Bresenhams_algorithm()
{
    int del_x = (ptArr[1].x - ptArr[0].x);
    int del_y = (ptArr[1].y - ptArr[0].y);

    int abs_del_x = abs(del_x);
    int abs_del_y = abs(del_y);

    if(abs_del_x==0)    //vertical line
    {
        glColor3f(1,0,0);
        float x_k = ptArr[0].x;
        float y_k = ptArr[0].y;
        glBegin(GL_POINTS);
            for(int s=0; s<=abs_del_y-1; s++)
            {
                glVertex2f(x_k, y_k);
                y_k += (del_y > 0) ? 1 : -1;
            }
        glEnd();
    }

    else if(abs_del_y==0)  //horizontal line
    {
        glColor3f(1,0,0);
        float x_k = ptArr[0].x;
        float y_k = ptArr[0].y;
        glBegin(GL_POINTS);
            for(int s=0; s<=abs_del_x-1; s++)
            {
                glVertex2f(x_k, y_k);
                x_k += (del_x > 0) ? 1 : -1;
            }
        glEnd();
    }

    else
    {
        glColor3f(0,0,0);

        if (abs_del_x >= abs_del_y)
        {
            float x_k = ptArr[0].x;
            float y_k = ptArr[0].y;
            int p_k = 2*abs_del_y - abs_del_x;

            glBegin(GL_POINTS);
                for(int s=0; s<=abs_del_x; s++)
                {
                    glVertex2f(x_k, y_k);

                    if(p_k < 0)
                    {
                        x_k += (del_x > 0) ? 1 : -1;
                        p_k += 2*abs_del_y;
                    }
                    else
                    {
                        x_k += (del_x > 0) ? 1 : -1;
                        y_k += (del_y > 0) ? 1 : -1;
                        p_k += 2*abs_del_y - 2*abs_del_x;
                    }
                }
            glEnd();
        }
        else
        {
            float x_k = ptArr[0].x;
            float y_k = ptArr[0].y;
            int p_k = 2*abs_del_x - abs_del_y;

            glBegin(GL_POINTS);
                for(int s=0; s<=abs_del_y-1; s++)
                {
                    glVertex2f(x_k, y_k);

                    if(p_k < 0)
                    {
                        y_k += (del_y > 0) ? 1 : -1;
                        p_k += 2 * abs_del_x;
                    }
                    else
                    {
                        x_k += (del_x > 0) ? 1 : -1;
                        y_k += (del_y > 0) ? 1 : -1;
                        p_k += 2*abs_del_x - 2*abs_del_y;
                    }
                }
            glEnd();
        }
    }
}




void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    showEndPoints();
    if(i==0)
    {
        //DDA_algorithm();
        Bresenhams_algorithm();
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
            cout <<"draw line" <<endl;
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
