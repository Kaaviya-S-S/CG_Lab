#ifdef _APPLE_
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
bool done = false;
int reflection = 0;


//to alter the coordinates range
void init()
{
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0,640,0,480);
}


void Reflection_x()
{
	for(int j=0; j<i; j++)
	{
    	ptArr[j].y *= -1;
	}
}

void Reflection_y()
{
	for(int j=0; j<i; j++)
	{
    	ptArr[j].x *= -1;
	}
}

void Reflection_yx()
{
	for(int j=0; j<i; j++)
	{
    	float temp = ptArr[j].x;
    	ptArr[j].x = ptArr[j].y;
    	ptArr[j].y = temp;
	}
}

void Reflection_y_x()
{
	for(int j=0; j<i; j++)
	{
    	float temp = ptArr[j].x;
    	ptArr[j].x = -ptArr[j].y;
    	ptArr[j].y = -temp;
	}
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);

	// x axis
	glBegin(GL_LINES);
    	glVertex2f(-1,0);
    	glVertex2f(1,0);
	glEnd();

	// y axis
	glBegin(GL_LINES);
    	glVertex2f(0,-1);
    	glVertex2f(0,1);
	glEnd();

	if(!done) //show endpoints
	{
    	glColor3f(1,0,0);
    	glBegin(GL_POINTS);
        	for (int j=0; j<i; j++)
        	{
            	glVertex2f(ptArr[j].x, ptArr[j].y);
        	}
    	glEnd();
	}

	if(done)
	{
    	glColor3f(1,0,0);
    	if(reflection==1)
    	{
        	cout <<"\nReflection about x-axis: " <<endl;
        	Reflection_x();
    	}
    	if(reflection==2)
    	{
        	cout <<"\nReflection about y-axis: " <<endl;
        	Reflection_y();
    	}
    	if(reflection==3)
    	{
        	cout <<"\nReflection about y=x axis: " <<endl;
        	Reflection_yx();
    	}
        if(reflection==4)
    	{
        	cout <<"\nReflection about y=-x axis: " <<endl;
        	Reflection_y_x();
    	}

    	glBegin(GL_LINE_LOOP);
        	for (int j=0; j<i; j++)
        	{
            	glVertex2f(ptArr[j].x, ptArr[j].y);
        	}
    	glEnd();
	}

	glFlush();
}


void mouse(int button, int state, int x, int y)
{
	glColor3f(0,0,1);
	glPointSize(2);
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
    	done = false;
    	cout <<"mouse current position: " <<x <<" " <<SCREEN_HEIGHT - y <<endl;
    	float normX = (x-320)/320.0f;
    	float normY = ((SCREEN_HEIGHT - y)-240)/240.0f;
    	cout <<"axis points: " <<normX <<" " <<normY <<endl;
    	ptArr[i].x = normX;
    	ptArr[i++].y = normY;
    	glutPostRedisplay();
	}
}


void keyboard(unsigned char key, int x, int y) {
	if(key == 13)  // ASCII code for Enter key
	{
    	done = true;
    	cout << "Drawing object completed." << endl;
    	glutPostRedisplay();
	}
}


void fillOption(int selectedOption)
{
	reflection = selectedOption;
	glutPostRedisplay();
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

	glutCreateMenu(fillOption);
	glutAddMenuEntry ("Reflection about x axis", 1);
	glutAddMenuEntry ("Reflection about y axis", 2);
	glutAddMenuEntry ("Reflection about y=x", 3);
	glutAddMenuEntry ("Reflection about y=-x", 4);
	glutAttachMenu (GLUT_RIGHT_BUTTON);

	glutMainLoop();
}

