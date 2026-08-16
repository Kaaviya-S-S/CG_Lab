#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLfloat ex=0.0, ey=0.0, ez=-6.0;
int windowWidth = 640, windowHeight = 480;

char projectionType = 'o'; // 'o'/'p'

// Function to update projection matrix
void updateProjection()
{
    double aspect = (double)windowWidth / (double)windowHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (projectionType=='p') {
        if (aspect < 1.0)
            glFrustum(-4.0, 4.0, -4.0/aspect, 4.0/aspect, 1.0, 10.0);
        else
            glFrustum(-4.0*aspect, 4.0*aspect, -4.0, 4.0, 1.0, 10.0);
    }
    else {
        if (aspect < 1.0)
            glOrtho(-4.0, 4.0, -4.0/aspect, 4.0/aspect, 1.0, 10.0);
        else
            glOrtho(-4.0*aspect, 4.0*aspect, -4.0, 4.0, 1.0, 10.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(ex, ey, ez, 0, 0, 0, 0, 1, 0);
}


void init()
{
    glEnable(GL_DEPTH_TEST);
    updateProjection();
}

GLfloat vertices[8][3] = {
    {-1.0, -1.0, -1.0}, {-1.0, -1.0, 1.0}, {-1.0, 1.0, -1.0}, {-1.0, 1.0, 1.0},
    {1.0, -1.0, -1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, -1.0}, {1.0, 1.0, 1.0}
};

//GLfloat pyramid[5][3] = {
//    {-1.0, 1.0, 1.0}, {-1.0, 1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, -1.0, -1.0}, {0.0, 2.0, 0.0}
//};


GLfloat colors[8][3] = {
    {0.5, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
    {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}
};


void resize(int width, int height) {
    if (height == 0) height = 1;
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
    updateProjection();
}


void draw_quad(int a, int b, int c, int d)
{
   glBegin(GL_QUADS);
       glVertex3fv(vertices[a]);
       glVertex3fv(vertices[b]);
       glVertex3fv(vertices[c]);
       glVertex3fv(vertices[d]);
   glEnd();

}


//void draw_pyramid(int a, int b, int c)
//{
//    glBegin(GL_POLYGON);
//        glVertex3fv(pyramid[a]);
//        glVertex3fv(pyramid[b]);
//        glVertex3fv(pyramid[c]);
//    glEnd();
//}

void mydraw()
{
    glColor3fv(colors[0]); draw_quad(6,7,5,4);
    glColor3fv(colors[1]); draw_quad(3,7,5,1);
    glColor3fv(colors[2]); draw_quad(0,1,3,2);
    glColor3fv(colors[3]); draw_quad(0,4,6,2);
    glColor3fv(colors[4]); draw_quad(2,3,7,6);
    glColor3fv(colors[5]); draw_quad(0,1,5,4);

//    glColor3fv(colors[7]); draw_pyramid(0,1,4);
//    glColor3fv(colors[7]); draw_pyramid(1,2,4);
//    glColor3fv(colors[7]); draw_pyramid(3,3,4);
}



void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mydraw();
    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case 'q': exit(0);
                  break;
        case '+': ez += 1.0;
                  break;
        case '-': ez -= 1.0;
                  break;
        case 'o': projectionType = 'o';
                  break;
        case 'p': projectionType = 'p';
                  break;
    }
    updateProjection();
    glutPostRedisplay();
}

void specialKey(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_LEFT : ex-=1.0;
                             break;
        case GLUT_KEY_RIGHT : ex+=1.0;
                             break;
        case GLUT_KEY_UP : ey+=1.0;
                             break;
        case GLUT_KEY_DOWN : ey-=1.0;
                             break;
    }
    updateProjection();
    glutPostRedisplay();
}

void idle() {
    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(80,80);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("3D projection");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutIdleFunc(idle);

    init();
    glutMainLoop();
}


