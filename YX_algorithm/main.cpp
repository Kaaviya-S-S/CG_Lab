#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdbool.h>
#include <bits/stdc++.h>
using namespace std;

#define SCREEN_HEIGHT 480  // Screen size 640 x 480
#define SCREEN_WIDTH 640

struct POINT2D {
    float x;
    float y;
};
POINT2D ptArr[50];

int i = 0;
bool polygon = false;
bool fillPolygon = false;


void init() {
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

float borderColor[3] = {0.0f, 0.0f, 0.0f};  // Black
float fillColor[3] = {1.0f, 0.0f, 0.0f};    // Red
float interiorColor[3] ={1.0f,1.0f,1.0f};   // White for flood fill algorithm


void setPixel(int x, int y)
{
    glColor3f(fillColor[0], fillColor[1], fillColor[2]);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}


int Intersection_Point_x(int x1, int y1, int x2, int y2, int l)   //(x1, y1, x2, y2, scanline - l)
{
    float m;
    if (x1 != x2)
        m = (float)(y2 - y1) / (x2 - x1);  // Use float division

    int x = x1 + (1.0f / m) * (l - y1);  // l is the scan line y-coordinate
    return x;
}


void YX_algorithm(int x[], int y[], int edges)
{
    // for each scan line k...
    for(int k=0; k<SCREEN_HEIGHT; k++)
    {
        int IntersectPt[edges], cnt = 0;

        //for each edge check if it intersects with the current scan line
        for(int j=0; j<edges; j++)
        {
            int next = (j+1)%edges;

            // Ignore horizontal edges (if edge directly coincide with scanline)
            if (y[j] == y[next])
                continue;

            if ( (y[j]>k && y[next]<=k) || (y[next]>k && y[j]<=k) )
            {
                //calculate intersection
                IntersectPt[cnt++] = Intersection_Point_x(x[j],y[j], x[next],y[next], k);
            }
        }

        // Sort the intersection points in ascending order
        sort(IntersectPt, IntersectPt + cnt);

        // Fill the pixels between pairs of intersection points
        if (cnt%2 == 0)
        {
            for (int j = 0; j < cnt; j += 2)
            {
                for (int xFill = IntersectPt[j]; xFill < IntersectPt[j + 1]; xFill++) {
                    setPixel(xFill, k);
                }
            }
        }
    }
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(borderColor[0], borderColor[1], borderColor[2]);

    if(!polygon)
	{
    	glBegin(GL_POINTS);
        	for (int j=0; j<i; j++)
        	{
            	glVertex2f(ptArr[j].x, ptArr[j].y);
        	}
    	glEnd();
	}
	if(polygon)
    {
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < i; j++)
        {
            glVertex2f(ptArr[j].x, ptArr[j].y);
        }
        glEnd();

        if(fillPolygon)
        {
            int x[50], y[50];
            for (int j = 0; j < i; j++)
            {
                x[j] = ptArr[j].x;
                y[j] = ptArr[j].y;
            }
            cout <<"calling YX algorithm.." <<endl;
            YX_algorithm(x,y,i);   //(x_pt of vertices, y_pt of vertices, no. of edges)
            cout <<"Done.." <<endl;
        }
    }

    glFlush();
}


void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        ptArr[i].x = x;
        ptArr[i++].y = SCREEN_HEIGHT - y;
        cout << "curr pos: " << x << " " << SCREEN_HEIGHT - y << endl;
        glutPostRedisplay();
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        cout <<"Draw polygon..." <<endl;
        polygon = true;
        glutPostRedisplay();
    }
}


void keyboard(unsigned char key, int x, int y)
{
	if(key == 13)  // ASCII code for Enter key
	{
        if(polygon)
        {
            cout <<"Fill polygon" <<endl;
            fillPolygon = true;
            glutPostRedisplay();
        }
	}
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Polygon Filling");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
