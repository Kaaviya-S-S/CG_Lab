/*
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
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

// q1) figure 1
void square_annulus_1()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0,0,1);
        glVertex2f(40, 40);
        glVertex2f(80, 80);
        glVertex2f(200, 40);
        glVertex2f(160, 80);
        glVertex2f(200, 200);
        glVertex2f(160, 160);
        glVertex2f(40,200);
        glVertex2f(80,160);
        glVertex2f(40,40);
        glVertex2f(80,80);
    glEnd();
}

// q1) figure 2
void square_annulus_2()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1,0,0);
        glVertex2f(20, 160);
        glVertex2f(20, 200);
        glVertex2f(80, 160);
        glVertex2f(120, 200);
        glVertex2f(80, 40);
        glVertex2f(120, 80);
        glVertex2f(200,40);
        glVertex2f(160,80);
        glVertex2f(200,160);
        glVertex2f(160,200);
        glVertex2f(260,160);
        glVertex2f(260,200);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //square_annulus_1();
    //square_annulus_2();

    glFlush();
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

    glutMainLoop();
}
*/


//-------------------------------------------------------------

/*
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
using namespace std;

#define SCREEN_HEIGHT 480

struct POINT2D
{
    float x;
    float y;
};
POINT2D ptArr[50];
int i=0;
int j=0;


void init()
{
    glClearColor(0.5,0.5,0.5,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void checkerboard()
{
    float x1 = ptArr[0].x;
    float y1 = ptArr[0].y;
    float x2 = ptArr[1].x;
    float y2 = ptArr[1].y;

    int rows = 8;
    int cols = 8;
    float width = (x2 - x1)/cols;
    float height = (y2 - y1)/rows;

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if((i+j)%2==0)
                glColor3f(1,1,1);
            else
                glColor3f(0,0,0);

            glBegin(GL_QUADS);
                glVertex2f(x1 + j*width, y1 + i*height);
                glVertex2f(x1 + (j+1)*width, y1 + i*height);
                glVertex2f(x1 + (j+1)*width, y1 + (i+1)*height);
                glVertex2f(x1 + j*width, y1 + (i+1)*height);
            glEnd();
        }
    }


}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (i==0)
        checkerboard();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    glColor3f(0,0,1);
    glPointSize(2);
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        ptArr[i].x = x;
        ptArr[i++].y = SCREEN_HEIGHT - y;
        cout <<"Current position: " <<x <<" " <<y <<endl;
        glBegin(GL_POINTS);
            glVertex2f(x, SCREEN_HEIGHT-y);
        glEnd();
        glFlush();

        if (i==2)
        {
            cout <<"checkerboard" <<endl;
            i=0;
            glutPostRedisplay();
        }
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
    glutMouseFunc(mouse);
    glutDisplayFunc(display);

    glutMainLoop();
}
*/

//-------------------------------------------------------------

/*
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
using namespace std;

#define SCREEN_HEIGHT 480


float initialKitePositions[3][2] = { {0, 0}, {150, 60}, {80, 120} };
float kitePositions[3][2] = { {0, 0}, {150, 60}, {80, 120} };
float kiteSpeed = 0.05f;


void init()
{
    glClearColor(0.6,1,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}


void drawKite(float bodyColor[3], float tailColor[3])
{
    glBegin(GL_QUADS);
        glColor3f(bodyColor[0], bodyColor[1], bodyColor[2]);
        glVertex2f(40, 120);
        glVertex2f(85, 140);
        glVertex2f(90, 95);
        glVertex2f(40, 60);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(tailColor[0], tailColor[1], tailColor[2]);
        glVertex2f(40, 60);
        glVertex2f(42, 46);
        glVertex2f(25, 55);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(40, 60);
        glVertex2f(85, 140);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(90, 95);
        glVertex2f(40, 120);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(0, 0, 0);
        glVertex2f(40, 60);
        glVertex2f(50, 50);
        glVertex2f(55, 40);
        glVertex2f(50, 20);
        glVertex2f(60, 10);
    glEnd();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float yellow[3] = {1.0, 1.0, 0.0};       // Yellow
    float pink[3] = {1.0, 0.0, 0.498};       // Pink
    float red[3] = {1.0, 0.0f, 0.0};         // Red
    float green[3] = {0.0, 1.0, 0.0};        // Green
    float violet[3] = {0.4, 0.0, 0.8};       // Violet
    float orange[3] = {1.0, 0.698, 0.4};     // Orange

    glPushMatrix();                                                     // Save the current matrix
        glTranslatef(kitePositions[0][0], kitePositions[0][1], 0);
        drawKite(pink, yellow);                                         // Original kite
    glPopMatrix();                                                      // Restore the saved matrix

    glPushMatrix();
        glTranslatef(kitePositions[1][0], kitePositions[1][1], 0);   // Translate kite position
        glScalef(1.5, 1.5, 1);                                       // Scale up the kite to 1.5x size
        drawKite(green, red);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(kitePositions[2][0], kitePositions[2][1], 0);    // Translate kite to the right and up
        glScalef(0.65, 0.65, 1);                                      // Scale up the kite to 0.95x size
        drawKite(violet, orange);
    glPopMatrix();

    glFlush();
}


void handleSpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        kiteSpeed += 0.01f;  // Increase the speed
    }
    else if (key == GLUT_KEY_DOWN)
    {
        kiteSpeed = (kiteSpeed > 0.01f) ? kiteSpeed - 0.01f : 0.0f;  // Decrease the speed but not below 0
    }

    glutPostRedisplay();
}



void idle()
{
    for (int i = 0; i < 3; ++i)
    {
        kitePositions[i][0] += kiteSpeed;  // Move kite - right
        kitePositions[i][1] += kiteSpeed;  // Move kite - up

        // Boundary check (bounce back when hitting top or bottom of the window)
        if (kitePositions[i][0] > 640 || kitePositions[i][0] < 0 || kitePositions[i][1] > 480 || kitePositions[i][1] < 0)
        {
            //reset the position to initial position
            kitePositions[i][0] = initialKitePositions[i][0];
            kitePositions[i][1] = initialKitePositions[i][1];
        }
    }

    glutPostRedisplay();  // Redraw the scene
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
    glutIdleFunc(idle);
    glutSpecialFunc(handleSpecialKeys);
    glutMainLoop();
}
*/

//-------------------------------------------------------------


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
using namespace std;

#define SCREEN_HEIGHT 480

struct POINT2D
{
    float x;
    float y;
};
POINT2D ptArr[50];
int i=0;

bool isPolygonComplete = false;
bool chooseColor = false;
float colorX = 0;
float colorY = 0;
float Colors[10][3] = {  {1.0, 0.0, 0.0},  // Red
                         {0.0, 1.0, 0.0},  // Green
                         {0.0, 0.0, 1.0},  // Blue
                         {1.0, 1.0, 0.0},  // Yellow
                         {1.0, 0.0, 1.0},  // Magenta
                         {0.0, 1.0, 1.0},  // Cyan
                         {0.4, 0.0, 0.8},   // Violet
                         {1.0, 0.0, 0.498}, //pink
                         {1.0, 0.698, 0.4}, //peach
                         {0.0, 0.0, 0.0}    //black
                      };

void init()
{
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}


 void drawPalette()
 {
    int cols = 2;
    int rows = 5;
    int width = 50;
    int height = 50;

    int x = 30;
    int y = 100;

    int k = 0;

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            glColor3f(Colors[k][0], Colors[k][1], Colors[k][2]);

            glBegin(GL_QUADS);
                glVertex2f(x + j*width, y + i*height);
                glVertex2f(x + (j+1)*width, y + i*height);
                glVertex2f(x + (j+1)*width, y + (i+1)*height);
                glVertex2f(x + j*width, y + (i+1)*height);
            glEnd();
            //cout <<k <<": " <<(x + j*width) <<" " <<(y + i*height) <<" & " <<(x + (j+1)*width) <<" "  <<(y + (i+1)*height) <<endl;
            k++;
        }
    }

 }


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1);
    glPointSize(3);
    glBegin(GL_POINTS);
        for (int j = 0; j < i; j++) {
            glVertex2f(ptArr[j].x, ptArr[j].y);
        }
    glEnd();

    if (isPolygonComplete && !chooseColor)
    {
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
            for (int j = 0; j < i; j++) {
                glVertex2f(ptArr[j].x, ptArr[j].y);
            }
        glEnd();

        glColor3f(0, 0, 0);  // Black outline color for polygon
        glBegin(GL_LINE_LOOP);
            for (int j = 0; j < i; j++) {
                glVertex2f(ptArr[j].x, ptArr[j].y);
            }
        glEnd();

        drawPalette();
    }



    else if (isPolygonComplete && chooseColor)
    {
        int l = i-1;
        float x = colorX;
        float y = colorY;

        if (x>30 && y>100 && x<130 && y<350)
        {
            int width = 50;  // Width of each color square
            int height = 50; // Height of each color square

            // Calculate which row and column were clicked
            int c = (x - 30) / width;
            int r = (y - 100) / height;

            int colorIndex = r * 2 + c;

            if (colorIndex >= 0 && colorIndex < 10) {
                // Change the polygon color to the selected color
                glColor3f(Colors[colorIndex][0], Colors[colorIndex][1], Colors[colorIndex][2]);
            }

        }
        else
            glColor3f(1,1,1);


        glBegin(GL_POLYGON);
            for (int j = 0; j < i; j++) {
                glVertex2f(ptArr[j].x, ptArr[j].y);
            }
        glEnd();

        glColor3f(0, 0, 0);  // Black outline color for polygon
        glBegin(GL_LINE_LOOP);
            for (int j = 0; j < i; j++) {
                glVertex2f(ptArr[j].x, ptArr[j].y);
            }
        glEnd();

        drawPalette();
    }

    glFlush();
}


void mouse(int button, int state, int x, int y)
{
    glColor3f(0,0,1);
    glPointSize(5);
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(chooseColor)
        {
            colorX = x;
            colorY = SCREEN_HEIGHT - y;
        }
        else
        {
            ptArr[i].x = x;
            ptArr[i++].y = SCREEN_HEIGHT - y;
        }
        cout <<"Current position: " <<x <<" " <<SCREEN_HEIGHT - y <<endl;
        glutPostRedisplay();
    }

    else if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)    //after clicking points, right click to draw and display
    {
        isPolygonComplete = true;
        cout <<"Drawing object" <<endl;
        glutPostRedisplay();
        chooseColor = true;
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
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutMainLoop();
}


//-------------------------------------------------------------

/*
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;


int sales[] = {2000, 4000, 7000, 6000, 4000, 8000, 8000, 7000, 5000, 6000, 8000, 9000};
string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"};


void init()
{
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,14,0,12000);
    glMatrixMode(GL_MODELVIEW);
}


void renderText(float x, float y, const char* text)
{
    glPushMatrix();
    glTranslatef(x, y, 0);  // Set the position for the text
    glScalef(0.01f, 0.01f, 0);  // Scale the text down
    for (const char* p = text; *p; p++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);  // Render each character
    }
    glPopMatrix();
}


void drawText(const char *text, float x, float y)
{
    glRasterPos2f(x, y);  // Set the text position
    for (const char *c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);  // Drawing character by character
    }
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 1.0);  // Set line color to blue
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 12; i++)
    {
        glVertex2f(i+1, sales[i]);
    }
    glEnd();


    //draw x-axis
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(0+1, 0+1000);
        glVertex2f(13, 0+1000);
    glEnd();

    //draw y-axis
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(0+1, 0+1000);
        glVertex2f(0+1, 11000);
    glEnd();


    //labels for x and y axis
    for (int i = 0; i < 12; i++)
    {
        //renderText(i + 1 - 0.2f, 500, months[i].c_str());  // Render the month names
        drawText(months[i].c_str(), i + 1, 700);
    }

    for (int y = 0; y <= 10000; y += 2000)
    {
        char label[10];
        sprintf(label, "%d", y);     // format the integer as string and store it in label
        drawText(label, 0.25f, y);   // Placing sales values next to the y-axis
    }

    glFlush();
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
    glutMainLoop();
}

*/

//-------------------------------------------------------------

/*
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <iostream>
using namespace std;


GLubyte diamond[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00,
    0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x00,
    0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x7E, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x7E, 0x00,
    0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x00,
    0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Polygon Stipple
    glEnable(GL_POLYGON_STIPPLE);
    glPolygonStipple(diamond);
    glBegin(GL_POLYGON);
    glVertex2f(200, 100);
    glVertex2f(400, 100);
    glVertex2f(400, 300);
    glVertex2f(200, 300);
    glEnd();
    glDisable(GL_POLYGON_STIPPLE);

    // line Stipple
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x1C47);
    glBegin(GL_LINE_LOOP);
    glVertex2f(190, 90);
    glVertex2f(410, 90);
    glVertex2f(410, 310);
    glVertex2f(190, 310);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glFlush();
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
    glutMainLoop();
}
*/
