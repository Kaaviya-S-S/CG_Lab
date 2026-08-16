#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
using namespace std;
#define SCREEN_HEIGHT 480 //screen size is considered as 640 x 480


struct POINT2D
{
    float x;
    float y;
};

POINT2D ptArr[50];
POINT2D ptArrClipped[50];

int i=0;
int k=0;

bool window = false;
bool line = false;
bool clipped = false;

int xw_min, yw_min, xw_max, yw_max;

// Define the region codes
const int INSIDE = 0;     // 0000
const int LEFT = 1;       // 0001
const int RIGHT = 2;      // 0010
const int BOTTOM = 4;     // 0100
const int TOP = 8;        // 1000



//to alter the coordinates range
void init()
{
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);

    /*cout <<"i: " <<i <<" " <<"k: " <<k <<endl;
    for (int j=0; j<i-1; j+=2)
    {
        cout <<ptArr[j].x <<" & " <<ptArr[j].y <<endl;
    }
    for (int j=0; j<k-1; j+=2)
    {
        cout <<ptArrClipped[j].x <<" & " <<ptArrClipped[j].y <<endl;;
    }*/


    if(!window)
    {
        glBegin(GL_POINTS);
            for (int j=0; j<i; j++)
            {
                glVertex2f(ptArr[j].x, ptArr[j].y);
            }
        glEnd();
    }

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

        glColor3f(1,0,0);
        glBegin(GL_LINES);
            for (int j = 0; j<i-1; j+=2)
            {
                glVertex2f(ptArr[j].x, ptArr[j].y);
                glVertex2f(ptArr[j + 1].x, ptArr[j + 1].y);
            }
        glEnd();

        if(clipped)
        {
            glColor3f(0,1,0);
            glBegin(GL_LINES);
                for (int j = 0; j<k-1; j+=2)
                {
                    glVertex2f(ptArrClipped[j].x, ptArrClipped[j].y);
                    glVertex2f(ptArrClipped[j + 1].x, ptArrClipped[j + 1].y);
                }
            glEnd();
        }
    }

    glFlush();
}


void mouse(int button, int state, int x, int y)
{
    glColor3f(0,0,0);
    glPointSize(2);
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        ptArr[i].x = x;
        ptArr[i++].y = SCREEN_HEIGHT - y;

        cout <<"Current position: " <<x <<" " <<SCREEN_HEIGHT - y <<endl;
        /*glBegin(GL_POINTS);
            glVertex2f(x, SCREEN_HEIGHT-y);
        glEnd();
        glFlush();
        */
        glutPostRedisplay();
    }
    else if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)    //after clicking points, right click to draw and display
    {
        if(!window and i>=2)
        {
            xw_min = ptArr[0].x;
            yw_min = ptArr[0].y;
            xw_max = ptArr[1].x;
            yw_max = ptArr[1].y;
            window = true;
            i = 0;
        }

        cout <<"Drawing object" <<endl;
        glutPostRedisplay();
    }
}


int Region_Code(POINT2D p)
{
    int code = INSIDE;
    int x = p.x;
    int y = p.y;

    if (x < xw_min)
        code |= LEFT;
    else if (x > xw_max)
        code |= RIGHT;

    if (y < yw_min)
        code |= BOTTOM;
    else if (y > yw_max)
        code |= TOP;

    return code;
}


void Cohen_SutherLand_algo()
{
    //cout <<"\nWindow: " <<xw_min <<" " <<xw_max <<" and " <<yw_min <<" " <<yw_max <<endl;

    for(int j=0; j<i-1; j+=2)
    {
        POINT2D p1 = ptArr[j];
        POINT2D p2 = ptArr[j+1];

        int code1 = Region_Code(p1);
        int code2 = Region_Code(p2);

        //cout <<"p1: " <<p1.x<<","<<p1.y <<" " <<"p2: " <<p2.x<<","<<p2.y <<endl;

        bool accept = false;

        ptArrClipped[k++] = p1;
        ptArrClipped[k++] = p2;

        while (true)
        {
            int t;
            //cout <<"p1 code: " <<code1 <<" " <<"p2 code: " <<code2 <<endl;

            // If both endpoints lie within rectangle
            if ((code1 == 0) && (code2 == 0))
            {
                accept = true;
                break;
            }

            // If both endpoints are outside --> same region
            else if (code1 & code2)
            {
                k -= 2;                             // since the curr 2 point which we put in ptArrClipped is outside, we reject it!
                break;
            }

            // Line is partially visible
            else
            {
                int code_out;
                float x,y;

                //atleast one point outside -> pick it
                if(code1!=0)
                {
                    code_out = code1;
                    t = k-2;                    //out of 2 end point, selecting 1st endpoint
                    //cout <<k <<endl;
                }
                else
                {
                    code_out = code2;
                    t = k-1;                    //out of 2 end point, selecting 2nd endpoint
                    //cout <<k <<endl;
                }

                //find the intersection point
                // y = y1 + m * (x - x1)  and  x = x1 + 1/m * (y - y1)
                float m = (p2.y - p1.y)/(p2.x - p1.x);

                if (code_out & TOP)
                {
                    x = p1.x + (1/m)*(yw_max - p1.y);
                    y = yw_max;
                }
                else if (code_out & BOTTOM)
                {
                    x = p1.x + (1/m)*(yw_min - p1.y);
                    y = yw_min;
                }
                else if (code_out & RIGHT)
                {
                    y = p1.y + m*(xw_max - p1.x);
                    x = xw_max;
                }
                else if (code_out & LEFT)
                {
                    y = p1.y + m*(xw_min - p1.x);
                    x = xw_min;
                }


                if (code_out == code1)
                {
                    ptArrClipped[t].x = x;
                    ptArrClipped[t].y = y;
                    code1 = Region_Code(ptArrClipped[t]);
                }
                else
                {
                    ptArrClipped[t].x = x;
                    ptArrClipped[t].y = y;
                    code2 = Region_Code(ptArrClipped[t]);
                }
            }

        }
    }
}


void Liang_Barsky_algo()
{
    for(int j=0; j<i-1; j+=2)
    {
        POINT2D p1 = ptArr[j];
        POINT2D p2 = ptArr[j+1];

        float dx = (p2.x - p1.x);
        float dy = (p2.y - p1.y);

        // L, R, B, T
        float p[4] = {-dx, dx, -dy, dy};
        float q[4] = {p1.x-xw_min, xw_max-p1.x, p1.y-yw_min, yw_max-p1.y};

        float u1 = 0.0f;
        float u2 = 1.0f;

        for(int t=0; t<4; t++)
        {
            if (p[t] == 0)
            {
                if (q[t] < 0)
                    break;   //line completely outside
            }
            else
            {
                float u = q[t]/p[t];
                if (p[t] < 0)       // line - out to in
                {
                    u1 = max(u1, u);
                }
                else              // line - in to out
                {
                    u2 = min(u2, u);
                }
            }
        }

        if (u1 <= u2) // valid line segment in window
        {
            POINT2D clipped_p1, clipped_p2;

            clipped_p1.x = p1.x + u1*dx;
            clipped_p1.y = p1.y + u1*dy;

            clipped_p2.x = p1.x + u2*dx;
            clipped_p2.y = p1.y + u2*dy;

            ptArrClipped[k++] = clipped_p1;
            ptArrClipped[k++] = clipped_p2;
        }
    }
}


void keyboard(unsigned char key, int x, int y)
{
    if(key == 13)  // ASCII code for Enter key
    {
        cout << "Call clipping..." << endl;
        Cohen_SutherLand_algo();
        //Liang_Barsky_algo();
        cout <<"done" <<endl;
        clipped = true;
        glutPostRedisplay();
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
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}
