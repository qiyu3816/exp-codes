#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <bits/stdc++.h>
using namespace std;
#include <stdlib.h>
 
static GLsizei iMode = 1;
static GLfloat xRot = 0;
static GLfloat yRot = 0;
GLUquadricObj *obj;
 
void Initial(){
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_LINE);
}
 
void ChangeSize(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5, 1.5, -1.5, 1.5);
}
void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    switch(iMode){
    case 1:
        glutWireTetrahedron(); break;
    case 2:
        glutSolidTetrahedron(); break;
    case 3:
        glutWireOctahedron(); break;
    case 4:
        glutSolidOctahedron(); break;
    case 5:
        glutWireSphere(1, 15, 15); break;
    case 6:
        glutSolidSphere(1, 15, 15); break;
    case 7:
        glutWireTeapot(1); break;
    case 8:
        glutSolidTeapot(1); break;
    case 9:
        gluSphere(obj, 1, 15, 15); break;
    case 10:
        gluCylinder(obj, 1, 0, 1, 15, 15); break;
    case 11:
        gluPartialDisk(obj, 0.3, 0.8, 15, 15, 30, 260); break;
    default: break;
    }
    glFlush();
}
 
void ProcessMenu(int value){
    iMode = value;
    glutPostRedisplay();
}
void SpecialKeys(int key, int x, int y){
    if(key == GLUT_KEY_UP) xRot -= 5;
    if(key == GLUT_KEY_DOWN) xRot += 5;
    if(key == GLUT_KEY_LEFT) yRot -= 5;
    if(key == GLUT_KEY_RIGHT) yRot += 5;
    if(xRot > 356) xRot = 0;
    if(xRot < -1) xRot = 355;
    if(yRot > 356) yRot = 0;
    if(yRot < -1) yRot = 355;
    glutPostRedisplay();
}
 
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("fuck");
 
    int nGlutPolyMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("REGULAR_TETRAHEDRON", 1); // ??????????????????
    glutAddMenuEntry("SOLID_TETRAHEDRON", 2);   // ??????????????????
    glutAddMenuEntry("REGULAR_OCTAHEDRON", 3);  // ??????????????????
    glutAddMenuEntry("SOLID_OCTAHEDRON", 4);    // ??????????????????
 
    int nGlutCurveMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("SPHERE_LOOP", 5);  // ????????????
    glutAddMenuEntry("SPHERE_SOLID", 6); // ????????????
    glutAddMenuEntry("TEAPOT_LOOP", 7);  // ????????????
    glutAddMenuEntry("TEAPOT_SOLID", 8); // ????????????
 
    int nGluCurveMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("SPHERE_LOOP", 9); // ????????????
    glutAddMenuEntry("CONE_LOOP", 10);  // ???????????????
    glutAddMenuEntry("RING_LOOP", 11);  // ???????????????
 
    int nMainMenu = glutCreateMenu(ProcessMenu);
    glutAddSubMenu("GLUT_POLYGON", nGlutPolyMenu);    // GLUT?????????
    glutAddSubMenu("GLUT_HOOK_FACE", nGlutCurveMenu); // GLUT?????????
    glutAddSubMenu("GLU_HOOK_FACE", nGluCurveMenu);   // GLU?????????
    glutAttachMenu(GLUT_RIGHT_BUTTON);
 
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    Initial();
    glutMainLoop();
}