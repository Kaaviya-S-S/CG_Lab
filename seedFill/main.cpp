/*
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
using namespace std;
#define SCREEN_HEIGHT 480    //screen size is considered as 640 x 480


struct POINT2D
{
   float x;
   float y;
};


float borderColor[3] = {0, 0, 0};    //black color
float fillColor[3] = {1, 0, 0};      //red color


//to alter the coordinates range
void init()
{
   glClearColor(1, 1, 1, 0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,640,0,480);
}


void setPixel(int x, int y)
{
   glColor3f(fillColor[0], fillColor[1], fillColor[2]);
   glBegin(GL_POINTS);
       glVertex2f(x,y);
   glEnd();
   glFlush();
}


void boundaryFill4(int x, int y)
{
    float interiorColor[3];

    // glReadPixels(xpos, ypos, width, height, format, type, return_data)
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, interiorColor);

    //cout <<interiorColor[0] <<" " <<interiorColor[1] <<" " <<interiorColor[2] <<endl;
    //float normInteriorColor[3] = {interiorColor[0]/255.0f, interiorColor[1]/255.0f, interiorColor[2]/255.0f};

    if((borderColor[0]!=interiorColor[0] || borderColor[1]!=interiorColor[1] || borderColor[2]!=interiorColor[2])
    && (fillColor[0]!=interiorColor[0] || fillColor[1]!=interiorColor[1] || fillColor[2]!=normInteriorColor[2]))
    {
       setPixel(x,y);
       boundaryFill4(x+1, y);
       boundaryFill4(x-1, y);
       boundaryFill4(x, y+1);
       boundaryFill4(x, y-1);
    }
}


void display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(borderColor[0], borderColor[1], borderColor[2]);
   glBegin(GL_LINE_LOOP);
       glVertex2f(100,100);
       glVertex2f(100,200);
       glVertex2f(150,250);
       glVertex2f(200,200);
       glVertex2f(200,100);
   glEnd();
   glFlush();
}


void mouse(int button, int state, int x, int y)
{
   glColor3f(1,0,0);
   if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
   {
       //ptArr[i].x = x;
       //ptArr[i++].y = SCREEN_HEIGHT - y;
       cout <<"filling start position: " <<x <<" " <<SCREEN_HEIGHT-y <<endl;

       cout <<borderColor[0] <<" " <<borderColor[1] <<" " <<borderColor[2] <<endl;
       cout <<fillColor[0] <<" " <<fillColor[1] <<" " <<fillColor[2] <<endl <<endl;

       boundaryFill4(x, SCREEN_HEIGHT-y);
       glFlush();
   }
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);


   glutInitWindowPosition(80,80);
   glutInitWindowSize(640,480);
   glutCreateWindow("polygon filling");


   init();
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutMainLoop();
}
*/
//-----------------------------------------------------------


#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdbool.h>
#include <iostream>
#include <stack>
using namespace std;

#define SCREEN_HEIGHT 480  // Screen size 640 x 480

struct POINT2D {
    float x;
    float y;
};

struct POINT2D_temp {
    float x;
    float y;
    char ch;
};

int i = 0;
POINT2D ptArr[50];
bool done = false;
int seed_x, seed_y;

void init() {
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

float borderColor[3] = {0.0f, 0.0f, 0.0f};  // Black
float fillColor[3] = {1.0f, 0.0f, 0.0f};    // Red

void setPixel(int x, int y)
{
    glColor3f(fillColor[0], fillColor[1], fillColor[2]);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
    glFlush();
}

void boundaryFill4(int x, int y)
{
    std::stack<POINT2D_temp> s;
    s.push({x, y, 'l'});

    for(int r=0; r<25; r++)
    {
        POINT2D_temp pt = s.top();
        s.pop();

        int px = pt.x;
        int py = pt.y;

        unsigned char interiorColor[3];  // Use GL_UNSIGNED_BYTE for better precision
        glReadPixels(px, py, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, interiorColor);

        /*
        cout <<"interior: " <<interiorColor[0] <<" " <<interiorColor[1] <<" " <<interiorColor[2] <<" " <<pt.ch<<endl;
        //cout <<"border: " <<borderColor[0] <<" " <<borderColor[1] <<" " <<borderColor[2] <<endl;
        //cout <<"fillcolor: " <<fillColor[0] <<" " <<fillColor[1] <<" " <<fillColor[2] <<endl <<endl;
        cout <<"border: "  <<(borderColor[0] != interiorColor[0] || borderColor[1] != interiorColor[1] || borderColor[2] != interiorColor[2]) <<endl;
        cout <<"fillcolor: " <<(fillColor[0] != interiorColor[0] || fillColor[1] != interiorColor[1] || fillColor[2] != interiorColor[2]) <<endl;

        if ((borderColor[0] != interiorColor[0] || borderColor[1] != interiorColor[1] || borderColor[2] != interiorColor[2])
            && (fillColor[0] != interiorColor[0] || fillColor[1] != interiorColor[1] || fillColor[2] != interiorColor[2])) {
        */
        float normInteriorColor[3] = {
            interiorColor[0] / 255.0f,
            interiorColor[1] / 255.0f,
            interiorColor[2] / 255.0f
        };

        cout << "\ninterior: " << normInteriorColor[0] << " " << normInteriorColor[1] << " " << normInteriorColor[2] << " " << pt.ch << endl;
        cout << "border: " << (borderColor[0] != normInteriorColor[0] || borderColor[1] != normInteriorColor[1] || borderColor[2] != normInteriorColor[2]) << endl;
        cout << "fillcolor: " << (fillColor[0] != normInteriorColor[0] || fillColor[1] != normInteriorColor[1] || fillColor[2] != normInteriorColor[2]) << endl;

        if ((borderColor[0] != normInteriorColor[0] || borderColor[1] != normInteriorColor[1] || borderColor[2] != normInteriorColor[2])
            && (fillColor[0] != normInteriorColor[0] || fillColor[1] != normInteriorColor[1] || fillColor[2] != normInteriorColor[2])) {

            setPixel(px, py);
            cout <<px <<" " <<py <<endl;

            float IntColor[3];
            glReadPixels(px, py, 1, 1, GL_RGB, GL_FLOAT, IntColor);
            cout << "after setting interior: " << IntColor[0] << " " << IntColor[1] << " " << IntColor[2] << " " << pt.ch << endl;

            s.push({px + 1, py, 'r'});
            s.push({px - 1, py, 'l'});
            s.push({px, py + 1, 't'});
            s.push({px, py - 1, 'b'});
        }
    }
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(borderColor[0], borderColor[1], borderColor[2]);
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < i; j++)
    {
        glVertex2f(ptArr[j].x, ptArr[j].y);
    }
    glEnd();  // Fixed

    if (done)
    {
        cout <<"\ndisplay: " <<seed_x <<" " <<seed_y <<endl;
        boundaryFill4(seed_x, seed_y);
    }
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        ptArr[i].x = x;
        ptArr[i++].y = SCREEN_HEIGHT - y;  // Fix y flip
        cout << "Start position: " << x << " " << SCREEN_HEIGHT - y << endl;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        cout <<"seed selected!" <<endl;
        seed_x = x;
        seed_y = SCREEN_HEIGHT - y;  // Fix y flip
        boundaryFill4(seed_x, seed_y);
        glFlush();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Polygon Filling");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}
