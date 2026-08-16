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
POINT2D ptArrTemp[50];

int i=0;
int k=0;

bool window = false;
bool polygon = false;
bool clipped = false;

int xw_min, yw_min, xw_max, yw_max;

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
	else if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)	//after clicking points, right click to draw and display
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


char find_position(int p, char bound) //check position w.r.t boundary
{
    char pos;
    switch(bound)
    {
        case 'l':   if(p > xw_min)   //inside of left boundary
                        pos = 'i';
                    else
                        pos = 'o';
                    break;

        case 'r':   if(p < xw_max)   //inside of right boundary
                        pos = 'i';
                    else
                        pos = 'o';
                    break;

        case 'b':   if(p > yw_min)   //inside of bottom boundary
                        pos = 'i';
                    else
                        pos = 'o';
                    break;

        case 't':   if(p < yw_max)   //inside of top boundary
                        pos = 'i';
                    else
                        pos = 'o';
                    break;
    }
    return pos;
}


void intersection_point(POINT2D p1, POINT2D p2, char boundary)
{
    POINT2D iPt; //intersection point
    float m;

    if(p1.x!=p2.x)
        m = (p2.y - p1.y)/(p2.x - p1.x);

    if(boundary=='l')
    {
        iPt.x = xw_min;
        iPt.y = p1.y + (xw_min - p1.x)*m;
        ptArrClipped[k++] = iPt;
    }

    else if(boundary=='r')
    {
        iPt.x = xw_max;
        iPt.y = p1.y + (xw_max - p1.x)*m;
        ptArrClipped[k++] = iPt;
    }

    else if(boundary=='b')
    {
        iPt.y = yw_min;
        if(p1.x!=p2.x)
            iPt.x = p1.x + (yw_min - p1.y)*(1/m);
        else    // vertical line
            iPt.x = p2.x;
        ptArrClipped[k++] = iPt;
    }

    else if(boundary=='t')
    {
        iPt.y = yw_max;
        if(p1.x!=p2.x)
            iPt.x = p1.x + (yw_max - p1.y)*(1/m);
        else    // vertical line
            iPt.x = p2.x;
        ptArrClipped[k++] = iPt;
    }
}


void Sutherland_Hodgman_algo()
{
	//copy the original points to a temp arr --> to ensure we have the original points for display after clipping
	int t=0; //iter var for temp arr
    for (int j=0; j<i; j++)
    {
        ptArrTemp[t++] = ptArr[j];
    }

	char pos;
	char bounds[4] = {'l','b','r','t'};

	for(int z=0; z<4; z++)
	{
	    k = 0; //reset the clipped point arr to empty
	    char boundary = bounds[z];
	    cout <<boundary <<endl;

        for(int j=0; j<t-1; j++)
        {
            POINT2D pt1 = ptArrTemp[j];
            POINT2D pt2 = ptArrTemp[j+1];

            char p1, p2;
            if(boundary=='l' || boundary=='r')
            {
                p1 = find_position(pt1.x, boundary);
                p2 = find_position(pt2.x, boundary);
            }
            else //top or bottom
            {
                p1 = find_position(pt1.y, boundary);
                p2 = find_position(pt2.y, boundary);
            }

            cout <<endl;
            cout <<p1 <<" " <<p2 <<endl;
            cout <<pt1.x <<"," <<pt1.y <<endl;
            cout <<pt2.x <<"," <<pt2.y <<endl;

            if(p1=='i' && p2=='i')
            {
                ptArrClipped[k++] = pt2;
            }
            else if(p1=='i' && p2=='o')
            {
                intersection_point(pt1, pt2, boundary);
            }
            else if(p1=='o' && p2=='i')
            {
                intersection_point(pt1, pt2, boundary);
                ptArrClipped[k++] = pt2;
            }

            else if(p1=='o' && p2=='o')
            {
                continue;    //discard
            }
        }

        //closing point
        ptArrClipped[k].x = ptArrClipped[0].x;
        ptArrClipped[k++].y = ptArrClipped[0].y;


        //copy the clipped points to the temp arr and pass it as input to next boundary check
        t = 0;
        for (int j=0; j<k; j++)
        {
            ptArrTemp[t++] = ptArrClipped[j];
        }

        cout <<"\n" <<"new points: " <<endl;
        for (int j=0; j<k; j++)
        {
            cout <<ptArrClipped[j].x <<" " <<ptArrClipped[j].y <<endl;
        }

        cout <<"*****************************************************************" <<endl <<endl;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if(key == 13)  // ASCII code for Enter key
	{
    	cout <<"Call polygon clipping..." <<endl;
    	Sutherland_Hodgman_algo();
    	cout <<"done" <<endl;
    	clipped = true;
    	glutPostRedisplay();
	}

	if(key==32)
	{
    	//add the 1st point as closing point for polygon
    	ptArr[i].x = ptArr[0].x;
    	ptArr[i++].y = ptArr[0].y;
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
	glutCreateWindow("drawing");

	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}

