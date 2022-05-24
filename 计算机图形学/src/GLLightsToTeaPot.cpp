/**
 * 画茶壶 设置不同颜色的三个光源
 */
#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

static GLfloat xRot = 0; // x旋转量
static GLfloat yRot = 0; // y旋转量
GLUquadricObj *obj;

/**
 * 初始化对象
 */
void Initial()
{
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_LINE);
}

/**
 * 显示主函数
 */
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat points[3][4] = {
        -2.0, 0, 0, 1,
        2.0, 2.0, 2.0, 1,
        -2.0, -2.0, 2.0, 1};

    GLfloat colors[3][4] = {
        0, 1.0, 0, 1,
        1.0, 0, 0, 1,
        0, 0, 1.0, 1};

    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, colors[0]); // 两种光照属性叠加效果更好
    glLightfv(GL_LIGHT0, GL_AMBIENT, colors[0]);
    glLightfv(GL_LIGHT0, GL_POSITION, points[0]);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, colors[1]);
    glLightfv(GL_LIGHT1, GL_AMBIENT, colors[1]);
    glLightfv(GL_LIGHT1, GL_POSITION, points[1]);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, colors[2]);
    glLightfv(GL_LIGHT2, GL_AMBIENT, colors[2]);
    glLightfv(GL_LIGHT2, GL_POSITION, points[2]);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glutWireTeapot(0.5);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL");

    glutDisplayFunc(Display);    // 显示
    Initial();
    glutMainLoop();
}