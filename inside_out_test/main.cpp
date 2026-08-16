#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdbool.h>
#include <iostream>
using namespace std;

#define SCREEN_HEIGHT 480  // Screen size 640 x 480

struct POINT2D {
    float x;
    float y;
};

int c = 0;
POINT2D ptArr[50];
bool done = false;

void init() {
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

float borderColor[3] = {0.0f, 0.0f, 0.0f};  // Black
float fillColor[3] = {1.0f, 0.0f, 0.0f};    // Red

void setPixel(int x, int y) {
    glColor3f(fillColor[0], fillColor[1], fillColor[2]);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

// Function to compute the Winding Number for a given point (px, py)
int InsideOut(int px, int py, int x[], int y[], int edges) {
    float px1, py1, px2, py2;
    float m, c;
    int intersections = 0;

    for (int i = 0; i < edges; i++) {
        px1 = x[i];
        py1 = y[i];
        px2 = x[(i + 1) % edges]; // Wrap around to the first vertex
        py2 = y[(i + 1) % edges];

        if (py1 > py2) { // Ensure py1 <= py2
            std::swap(px1, px2);
            std::swap(py1, py2);
        }

        // Check if the point lies between the y-values of the current edge
        if (!(py >= py1 && py < py2)) {
            continue;
        }

        // Calculate slope and intercept of the edge
        m = (py2 - py1) / (px2 - px1);
        c = py1 - m * px1;

        // Count if the point is to the left of the intersection
        if (px <= (py - c) / m) {
            intersections++;
        }
    }

    // Return whether the winding number indicates inside (non-zero) or outside (zero)
    return intersections % 2; // Odd = inside, even = outside
}

void fillPolygonUsingInsideOut(int x[], int y[], int edges)
{
    int xmin = 640, xmax = 0, ymin = 480, ymax = 0;

    // Find bounding box
    for (int i = 0; i < edges; i++) {
        if (x[i] < xmin) xmin = x[i];
        if (x[i] > xmax) xmax = x[i];
        if (y[i] < ymin) ymin = y[i];
        if (y[i] > ymax) ymax = y[i];
    }

    // Iterate over each pixel inside the bounding box
    for (int px = xmin; px <= xmax; px++) {
        for (int py = ymin; py <= ymax; py++) {
            if (InsideOut(px, py, x, y, edges)) {
                setPixel(px, py);
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(borderColor[0], borderColor[1], borderColor[2]);
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < c; j++) {
        glVertex2f(ptArr[j].x, ptArr[j].y);
    }
    glEnd();

    if (done) {
        int x[50], y[50];
        for (int j = 0; j < c; j++) {
            x[j] = ptArr[j].x;
            y[j] = ptArr[j].y;
        }
        fillPolygonUsingInsideOut(x, y, c);
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        ptArr[c].x = x;
        ptArr[c++].y = SCREEN_HEIGHT - y;
        cout << "Start position: " << x << " " << SCREEN_HEIGHT - y << endl;
        glutPostRedisplay();
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        done = true;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Winding Number Polygon Filling");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}
