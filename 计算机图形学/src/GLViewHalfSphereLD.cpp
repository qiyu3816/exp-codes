/**
 * 在窗口左下角1/4处绘制半球
 */
#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

static GLfloat xRot = 0;         // x旋转量
static GLfloat yRot = 0;         // y旋转量
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
 * 调整窗口大小改变时的图形大小
 * 
 * @param w 当前窗口宽度放缩倍数
 * @param h 当前窗口高度放缩倍数
 */
void ChangeSize(int w, int h)
{
    glViewport(-w / 4, -h / 2, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 0, 1.5, -1.5);
}

/**
 * 显示主函数
 */
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glutSolidSphere(0.5, 20, 16);
    
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL");

    glutDisplayFunc(Display);     // 显示
    glutReshapeFunc(ChangeSize);  // 根据窗口大小调整图形大小
    Initial();
    glutMainLoop();
}