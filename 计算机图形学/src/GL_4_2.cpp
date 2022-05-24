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

const GLfloat lightPosition[] = {0.0, 0.0, 0.0, 0.0};
const GLfloat whiteLight[] = {0.8, 0.8, 0.8, 1.0};
GLfloat matSpecular[] = {0.3, 0.3, 0.3, 1.0};
GLfloat matShininess[] = {20.0};
GLfloat matEmission[] = {0.3, 0.3, 0.3, 1.0};

double my_angle = 0.0;

/**
 * 初始化对象
 */
void Initial()
{
    glClearColor(1, 1, 1, 1);
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRotatef(xRot, 1, 0, 0);                     // x轴旋转
    glRotatef(yRot, 0, 1, 0);                     // y轴旋转

    GLfloat material_Ke0[] = {0.24, 0.63, 0.3, 0.4};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke0); // 设置三个侧面的材质
    glColor3ub(0, 195, 195);
    glBegin(GL_QUADS);
        glVertex3f(0.3, 0.3, -0.5);
        glVertex3f(-0.3, 0.3, -0.5);
        glVertex3f(-0.3, -0.3, -0.5);
        glVertex3f(0.3, -0.3, -0.5);
    glEnd();
    glColor3ub(0, 195, 110);
    glBegin(GL_QUADS);
        glVertex3f(0.3, 0.3, -0.5);
        glVertex3f(0.3, -0.3, -0.5);
        glVertex3f(0.4, -0.3, 0.5);
        glVertex3f(0.4, 0.3, 0.5);
    glEnd();
    glColor3ub(0, 195, 0);
    glBegin(GL_QUADS);
        glVertex3f(-0.3, 0.3, -0.5);
        glVertex3f(-0.3, -0.3, -0.5);
        glVertex3f(-0.4, -0.3, 0.5);
        glVertex3f(-0.4, 0.3, 0.5);
    glEnd();
    GLfloat material_Ke1[] = {0.1, 0.5, 0.2, 0.4};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke1); // 设置底面和顶面的材质
    glColor3ub(10, 195, 0);
    glBegin(GL_QUADS);
        glVertex3f(-0.3, 0.3, -0.5);
        glVertex3f(0.3, 0.3, -0.5);
        glVertex3f(0.4, 0.3, 0.5);
        glVertex3f(-0.4, 0.3, 0.5);
    glEnd();
    glColor3ub(0, 195, 200);
    glBegin(GL_QUADS);
        glVertex3f(-0.3, -0.3, -0.5);
        glVertex3f(0.3, -0.3, -0.5);
        glVertex3f(0.4, -0.3, 0.5);
        glVertex3f(-0.4, -0.3, 0.5);
    glEnd();

    glRotatef(my_angle, 1.0, 0.5, 1.0);
    glTranslatef(0.1, 0.1, -0.1);
    GLfloat light0_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light0_specular[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat light0_ambient[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat light0_diffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0 , GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glutSolidSphere(0.05, 20, 20);

    glFlush();
}

/**
 * 角度更新函数 使用假设的值
 */
void MyIdel(void)
{
    my_angle += 10.0;
    if (my_angle >= 360)
        my_angle = 0.0;
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

    glutDisplayFunc(Display); // 显示
    glutIdleFunc(MyIdel);
    glutKeyboardFunc(NormalKeys); // 监听按键事件
    Initial();
    glutMainLoop();
}