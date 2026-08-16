#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <iostream>
using namespace std;

#define WIDTH 640
#define HEIGHT 480

struct point { float x,y; };

vector<point> ptArr;
float isBezier = true;

void init() {
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}


void drawPoints() {
    glColor3f(1, 1, 1);
    glBegin(GL_POINTS);
    for (size_t i = 0; i < ptArr.size(); ++i)
        glVertex2f(ptArr[i].x, ptArr[i].y);
    glEnd();
}


void drawControlPolygon() {
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_STRIP);
    for (size_t i = 0; i < ptArr.size(); ++i)
        glVertex2f(ptArr[i].x, ptArr[i].y);
    glEnd();
}


void drawBezierCurves()
{
    if(ptArr.size()<3) return;
    glColor3f(1,0,0);
    int k=3, n=4, knotCount = n+k+1;

    for(size_t i=0; i+3<ptArr.size(); i+=4)
    {
        float control[n*3];
        for(int j=0; j<n; j++)
        {
            control[j*3 + 0] = ptArr[i+j].x;
            control[j*3 + 1] = ptArr[i+j].y;
            control[j*3 + 2] = 0;
        }
        GLfloat knots[8] = {0,0,0,0,1,1,1,1};
        GLUnurbsObj* nurbs = gluNewNurbsRenderer();
        gluBeginCurve(nurbs);
        gluNurbsCurve(nurbs, knotCount, knots, 3, control, k+1, GL_MAP1_VERTEX_3);
        gluEndCurve(nurbs);
        gluDeleteNurbsRenderer(nurbs);
    }
}

void drawBSpline()
{
    if(ptArr.size()<3) return;
    glColor3f(1,0,0);
    int k=3, n=ptArr.size(), knotCount = n+k+1;
    GLfloat* knots = new GLfloat[knotCount];

    for(int i=0; i<knotCount; i++)
    {
        if(i<k)
            knots[i] = 0;
        else if(i<=n)
            knots[i] = (float) (i-k)/(n-k+1);
        else
            knots[i] = 1;
    }

    float control[n*3];
    for(int j=0; j<n; j++)
    {
        control[j*3 + 0] = ptArr[j].x;
        control[j*3 + 1] = ptArr[j].y;
        control[j*3 + 2] = 0;
    }
    GLUnurbsObj* nurbs = gluNewNurbsRenderer();
    gluBeginCurve(nurbs);
    gluNurbsCurve(nurbs, knotCount, knots, 3, control, k+1, GL_MAP1_VERTEX_3);
    gluEndCurve(nurbs);
    gluDeleteNurbsRenderer(nurbs);

    delete[] knots;
}

void keyboard(unsigned char key, int, int) {
    if (key == 'e') {
        ptArr.clear();
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
    if (key == 'b') isBezier = true;
    if (key == 's') isBezier = false;
}



void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        ptArr.push_back({(float)x, (float)(HEIGHT - y)});

        glClear(GL_COLOR_BUFFER_BIT);
        drawPoints();
        drawControlPolygon();
        if (isBezier) drawBezierCurves();
        else drawBSpline();

        glFlush();
    }
}



int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(80,80);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("bezier, bspline");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
