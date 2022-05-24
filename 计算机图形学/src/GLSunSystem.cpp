/**
 * 绘制简单相对运动太阳系 包括太阳、地球、月球
 * 
 * 分别用红色、蓝色、白色表示
 * 
 * i j k l键进行视角旋转 虽然没画轨迹 但是还是可以看出基本的运动规律
 */
#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include "time.h"

static GLfloat xRot = 0;         // x旋转量
static GLfloat yRot = 0;         // y旋转量
GLUquadricObj *obj;

double earthAngle = 0.0, moonAngle = 0.0;

/**
 * 初始化对象
 */
void Initial()
{
    glClearColor(0, 0, 0, 1);
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_LINE);
}

/**
 * 主显示函数
 */
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(xRot, 1, 0, 0);                     // x轴旋转
    glRotatef(yRot, 0, 1, 0);                     // y轴旋转

    glColor3f(1.0, 0, 0);
    glutSolidSphere(0.1, 20, 20);           // 太阳

    glColor3f(0.0, 0.0, 1.0);
    glRotated(earthAngle, 1.0, 1.0, 1.0);   // 地球绕太阳公转
    glTranslated(0.4, 0.4, -0.4);           // 地球公转半径和方向
    glutSolidSphere(0.03, 20, 20);

    glColor3f(1.0, 1.0, 1.0);
    glRotated(moonAngle, 1.0, 1.0, 1.0);    // 月球绕地球转
    glTranslated(-0.07, -0.07, 0.07);       // 月球旋转半径及方向
    glutSolidSphere(0.02, 20, 20);

    glFlush();
}

/**
 * 角度更新函数 使用假设的值
 */
void MyIdel(void)
{
    moonAngle += 10.0;
    earthAngle += 3.0;
    if(moonAngle >= 360)
        moonAngle = 0.0;
    if(earthAngle > 360)
        earthAngle = 0.0;
    Sleep(100);
    Display();
}

/**
 * 按键操作
 * 
 * @param key 当前按键
 * @param x 当前鼠标x坐标
 * @param y 当前鼠标y坐标
 */
void NormalKeys(unsigned char key, int x, int y)
{
    if (key == 'i')
        xRot -= 5;
    if (key == 'k')
        xRot += 5;
    if (key == 'j')
        yRot -= 5;
    if (key == 'l')
        yRot += 5;
    if (xRot > 356)
        xRot = 0;
    if (xRot < -1)
        xRot = 355;
    if (yRot > 356)
        yRot = 0;
    if (yRot < -1)
        yRot = 355;

    glutPostRedisplay();
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
    glutKeyboardFunc(NormalKeys); // 监听按键事件
    Initial();
    glutMainLoop();
}