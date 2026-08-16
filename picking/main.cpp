#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define WIDTH 600
#define HEIGHT 400

GLuint selectBuffer[512];
int selectedObject = -1;
bool isDragging = false;
float lastX, lastY;

struct Cube {
   float x, y, z;
   float r, g, b;
} cubes[3] = {
   {-1.5, 0, -6, 1, 0, 0},  // Red cube
   {0, 0, -6, 0, 1, 0},     // Green cube
   {1.5, 0, -6, 0, 0, 1}    // Blue cube
};

void init() {
   glClearColor(0.4, 0.4, 0.4, 1.0);
   glEnable(GL_DEPTH_TEST);
}

void drawCube(int id) {
   Cube c = cubes[id];
   glColor3f(c.r, c.g, c.b);
   if (selectedObject == id) {
       glColor3f(1, 1, 0); // Yellow for selected
   }

   glPushMatrix();
   glTranslatef(c.x, c.y, c.z);
   glutSolidCube(1);
   glPopMatrix();
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   for (int i = 0; i < 3; i++) {
       drawCube(i);
   }
   glutSwapBuffers();
}

void reshape(int w, int h) {
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60, (float)w/h, 1, 20);
   glMatrixMode(GL_MODELVIEW);
}

void processHits(int hits)
{
   GLuint* ptr = selectBuffer;
   selectedObject = -1;

   for (int i = 0; i < hits; i++) {
       int names = *ptr;
       ptr += 3;
       if (names > 0) {
           selectedObject = *ptr;
       }
       ptr += names;
   }
}

void pickObject(int x, int y)
{
   GLint viewport[4];
   glGetIntegerv(GL_VIEWPORT, viewport);

   glSelectBuffer(512, selectBuffer);
   glRenderMode(GL_SELECT);

   glInitNames();
   glPushName(0);

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();

   gluPickMatrix(x, viewport[3]-y, 5, 5, viewport);
   gluPerspective(60, (float)viewport[2]/viewport[3], 1, 20);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   for (int i = 0; i < 3; i++) {
       glLoadName(i);
       drawCube(i);
   }

   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);

   int hits = glRenderMode(GL_RENDER);
   processHits(hits);

   if (selectedObject != -1) {
       isDragging = true;
       lastX = x;
       lastY = y;
   }

   glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON) {
       if (state == GLUT_DOWN) {
           pickObject(x, y);
       } else {
           isDragging = false;
       }
   }
}

void motion(int x, int y)
{
   if (isDragging && selectedObject != -1) {
       // Calculate mouse movement difference
       float dx = (x - lastX) * 0.01;
       float dy = (lastY - y) * 0.01;

       // Update cube position
       cubes[selectedObject].x += dx;
       cubes[selectedObject].y += dy;

       lastX = x;
       lastY = y;
       glutPostRedisplay();
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(WIDTH, HEIGHT);
   glutCreateWindow("OpenGL Picking with Movement");

   init();

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);  // New callback for mouse movement

   glutMainLoop();
   return 0;
}
