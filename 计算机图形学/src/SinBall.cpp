/**
 * 绘制正弦运动的小球 和立方体抛物线运动
 * 
 * 正弦运动一个周期 抛物线在y坐标小于0时重置
 */
#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <thread>
#define GRAVITY_FACTOR 9.8

using namespace std;

GLUquadricObj *obj;
double xNsin = -0.6, xNpa = -0.6;
double yNsin = 0.6 * sin(6.0 * xNsin), yNpa = 0.9 - 0.5 * GRAVITY_FACTOR * (xNpa + 0.6) * (xNpa + 0.6);

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

    glTranslated(xNsin, yNsin, 0);
    glutWireSphere(0.1, 10, 10);
    glTranslated(-xNsin, -yNsin, 0);
    // std::cout << xNpa << "," << yNpa << std::endl;
    glTranslated(xNpa, yNpa, 0);
    glutWireCube(0.05);
    
    glFlush();
}

/**
 * 根据帧数递增x坐标
 */
void MyIdel(void)
{
    if(xNsin >= 0.6)
        xNsin = -0.6;
    if(yNpa < 0)
        xNpa = -0.6;
    xNsin += 0.01;
    yNsin = 0.6 * sin(6.0 * xNsin);
    xNpa += 0.01;
    yNpa = 0.9 - 0.5 * GRAVITY_FACTOR * (xNpa + 0.6) * (xNpa + 0.6);
    Sleep(100);
    Display();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL");

    glutDisplayFunc(Display);     // 显示
    glutIdleFunc(MyIdel);
    Initial();
    glutMainLoop();
}