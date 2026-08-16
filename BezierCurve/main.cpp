#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

#define SCREEN_HEIGHT 480	// screen size is 640 x 480
#define MAX_COUNT 50        // maximum number of curves

struct POINT2D {
    float x;
    float y;
};

POINT2D pt[4];                 // stores the points for the current curve
POINT2D curves[MAX_COUNT][4];  // stores the control points for all curves
int i = 0;
int CurveCount = 0;
bool done = false;

void init() {
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void BezierCurve(POINT2D* pt)
{
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1; t += 0.01)
    {
        int x, y;
        x = (pt[0].x)*pow(1-t,3) + 3*(pt[1].x)*(t)*pow(1-t,2) + 3*(pt[2].x)*(1-t)*pow(t,2) + (pt[3].x)*pow(t,3);
    	y = (pt[0].y)*pow(1-t,3) + 3*(pt[1].y)*(t)*pow(1-t,2) + 3*(pt[2].y)*(1-t)*pow(t,2) + (pt[3].y)*pow(t,3);
        glVertex2f(x, y);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);

    // Draw points and curves for all previously created curves
    for (int k = 0; k < CurveCount; k++)
    {
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < 4; j++) {
            glVertex2f(curves[k][j].x, curves[k][j].y);
        }
        glEnd();

        BezierCurve(curves[k]);  // Draw the Bezier curve for the stored points
    }
    done = false;


    // Draw the points of the current curve being clicked
    if (!done)
    {
        glColor3f(0, 0, 0);
        glBegin(GL_POINTS);
        for (int j = 0; j < i; j++) {
            glVertex2f(pt[j].x, pt[j].y);
        }
        glEnd();
    }

    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    glColor3f(0, 0, 0);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (i < 4)
        {
            pt[i].x = x;
            pt[i].y = SCREEN_HEIGHT - y;
            cout << "Position: " << x << " " << SCREEN_HEIGHT - y << endl;
            i++;  // Move to the next point
        }

        // Once 4 points are clicked, draw the curve
        if (i == 4 && CurveCount < MAX_COUNT)
        {
            for (int j = 0; j < 4; j++)
                curves[CurveCount][j] = pt[j];

            CurveCount++;
            i = 0;
            done = true;
        }

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(80, 80);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bezier Curve");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}
