#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
using namespace std;

void init()
{
   glClearColor(0, 0, 0, 0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,100,0,100);
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //GLubyte bitShape[15] = {0x0000, 0x0418, 0x0C30, 0x1460, 0x04C0, 0x0580, 0x0700, 0x0600, 0x0700, 0x0580, 0x04C0, 0x0460, 0x0430, 0x1C18, 0x0000};
    GLubyte bitShape[30] = {
        0x00, 0x00, // 0x0000
        0x04, 0x18, // 0x0418
        0x0C, 0x30, // 0x0C30
        0x14, 0x60, // 0x1460
        0x04, 0xC0, // 0x04C0
        0x05, 0x80, // 0x0580
        0x07, 0x00, // 0x0700
        0x06, 0x00, // 0x0600
        0x07, 0x00, // 0x0700
        0x05, 0x80, // 0x0580
        0x04, 0xC0, // 0x04C0
        0x04, 0x60, // 0x0460
        0x04, 0x30, // 0x0430
        0x1C, 0x18, // 0x1C18
        0x00, 0x00  // 0x0000
    };
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glRasterPos2i(20, 20);
    glBitmap(16, 15, 0.0, 0.0, 20.0, 15.0, bitShape);

    glFlush();
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);


   glutInitWindowPosition(80,80);
   glutInitWindowSize(640,480);
   glutCreateWindow("letter display");


   init();
   glutDisplayFunc(display);
   glutMainLoop();
}

