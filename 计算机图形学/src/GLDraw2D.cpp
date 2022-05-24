/**
 * 绘制二维图形 右键选择框切换绘制点 线 多边形等的线图和实体图 并可按方向键进行旋转
 */
#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

static const GLint window_width = 500;
static const GLint window_height = 500;
static GLsizei iMode = 1; // 当前状态
static GLfloat xRot = 0;  // x旋转量
static GLfloat yRot = 0;  // y旋转量
static GLfloat PI = 3.141592654;

/**
 * 画点
 */
void drawPoint(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // 画点
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
        glVertex2f(0.1, 0.1);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(0.3, 0.3);
    glEnd();

    glFlush();
}

/**
 * 画线
 */
void drawLine(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_LINE_STIPPLE);

    // 画线
    glLineWidth(6.0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex2f(-0.2, -0.2);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.3, 0.5);
    glEnd();

    glFlush();
}

/**
 * 画虚线
 */
void drawStippleLine(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // 画线
    glLineWidth(6.0);
    glLineStipple(3, 0x0F0F);  // 虚线样式
    glEnable(GL_LINE_STIPPLE); // 使能虚线
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex2f(-0.2, -0.2);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.3, 0.5);
    glEnd();

    glFlush();
}

/**
 * 画线框圆和椭圆
 */
void drawFrameEllipse(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_LINE_STIPPLE);
    
    glColor3f(0.0, 0.0, 1.0);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	    GLfloat rx = 260.f, ry = 150.f;
	    for (GLfloat angle = 0.0f; angle <= (2.0f * PI); angle += 0.01f)
	    {
	    	glVertex2f(rx * sin(angle) / window_width, ry * cos(angle) / window_height);
	    }
	glEnd();

    glFlush();
}

/**
 * 画实体圆和椭圆
 */
void drawSolidEllipse(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_LINE_STIPPLE);
    
    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
        GLfloat rx = 260.f, ry = 150.f;
	    for (GLfloat angle = 0.0f; angle <= (2.0f * PI); angle += 0.01f)
	    {
	    	glVertex2f(rx * sin(angle) / window_width, ry * cos(angle) / window_height);
	    }
    glEnd();

    glFlush();
}

/**
 * 画线框多边形
 */
void drawFramePolygon(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_LINE_STIPPLE);

    int n = 6;
    GLfloat vertex_list[][2] = {
        -0.3f, -0.256f,
         0.3f, -0.256f,
         0.45f, 0.0f,
         0.3f,  0.256f,
        -0.3f,  0.256f,
        -0.45f, 0.0f,
    };

    // 画多边形
    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++)
    {
        glVertex2f(vertex_list[i][0], vertex_list[i][1]);
    }
    glEnd();

    glFlush();
}

/**
 * 画实体多边形
 */
void drawSolidPolygon(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_LINE_STIPPLE);

    int n = 6;
    GLfloat vertex_list[][2] = {
        -0.3f, -0.256f,
         0.3f, -0.256f,
         0.45f, 0.0f,
         0.3f,  0.256f,
        -0.3f,  0.256f,
        -0.45f, 0.0f,
    };

    // 画多边形
    glBegin(GL_POLYGON); // 填充
    for (int i = 0; i < n; i++)
    {
        glVertex2f(vertex_list[i][0], vertex_list[i][1]);
    }
    glEnd();

    glFlush();
}

/**
 * 调整窗口大小改变时的图形大小
 */
void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5, 1.5, -1.5, 1.5);
}

/**
 * 显示主函数
 */
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    switch (iMode)
    {
    case 1:
        drawPoint();
        break;
    case 2:
        drawLine();
        break;
    case 3:
        drawStippleLine();
        break;
    case 4:
        drawFrameEllipse();
        break;
    case 5:
        drawSolidEllipse();
        break;
    case 6:
        drawFramePolygon();
        break;
    case 7:
        drawSolidPolygon();
        break;
    default:
        break;
    }
    glFlush();
}

/**
 * 处理菜单事件
 */
void ProcessMenu(int value)
{
    iMode = value;
    glutPostRedisplay();
}

/**
 * 方向键转换视角
 */
void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        xRot -= 5;
    if (key == GLUT_KEY_DOWN)
        xRot += 5;
    if (key == GLUT_KEY_LEFT)
        yRot -= 5;
    if (key == GLUT_KEY_RIGHT)
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
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL");

    int nGLU2dMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("POINT", 1);         // 点
    glutAddMenuEntry("LINE", 2);          // 线
    glutAddMenuEntry("STIPPLE_LINE", 3);  // 虚线
    glutAddMenuEntry("FRAME_ELLIPSE", 4); // 线框圆
    glutAddMenuEntry("SOLID_ELLIPSE", 5); // 实体圆
    glutAddMenuEntry("FRAME_POLYGON", 6); // 线框多边形
    glutAddMenuEntry("SOLID_POLYGON", 7); // 实体多边形
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(Display);     // 显示
    glutReshapeFunc(ChangeSize);  // 根据窗口大小调整图形大小
    glutSpecialFunc(SpecialKeys); // 监听按键事件
    glutMainLoop();
}