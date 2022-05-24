/**
 * 在窗口左下角1/4处绘制半球(运行目的错误代码)
 * 可以使用按键旋转
 * 
 * i j k l键进行旋转
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
    int dis = w < h ? w : h;
    glViewport(0, 0, dis, dis);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, 1.5, -1.5);
}

/**
 * 显示主函数
 */
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(xRot, 1, 0, 0);                     // x轴旋转
    glRotatef(yRot, 0, 1, 0);                     // y轴旋转

    // 定义圆心
    GLfloat centerX = -0.5f, centerY = -0.5f, centerZ = 0.2f;
    // 定义半径 假设半球的原平面朝向x轴正方向
    // 半球圆面的法向量朝向x轴负方向
    GLfloat radius = 0.4f;
    // 定义每个圆环取的点数和圆面到球面顶点的圆环层数
    GLint circlePoints = 10, layerNums = 5;
    // 声明存储所有点的向量集
    vector<vector<GLfloat>> circlePointss(layerNums, vector<GLfloat>(3 * circlePoints));
    // 计算圆环内相邻点的弧度差和相邻圆环间相对球心的弧度差
    GLfloat circleStep = 2 * M_PI / circlePoints, layerStep = M_PI / 2.0f / layerNums;
    for(int i = 0; i < layerNums; i++)
    {
        vector<GLfloat> curCircle(3 * circlePoints);
        for(int j = 0; j < circlePoints; j++)
        {
            GLfloat curX = centerX - radius * sin(layerStep * i);
            GLfloat curY = centerY - radius * cos(layerStep * i) * sin(circleStep * j);
            GLfloat curZ = centerZ - radius * cos(layerStep * i) * cos(circleStep * j);
            curCircle[3 * j] = curX;
            curCircle[3 * j + 1] = curY;
            curCircle[3 * j + 2] = curZ;
        }
        circlePointss[i] = curCircle;
    }

    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(1.0);
    
    // 第一层圆画出圆心和各点的连线
    for(int j = 0; j < circlePoints; j++)
    {
        glBegin(GL_LINE_LOOP);
            glVertex3f(centerX, centerY, centerZ);
            glVertex3f(circlePointss[0][3 * j], circlePointss[0][3 * j + 1], circlePointss[0][3 * j + 2]);
        glEnd();
    }
    // 画每一层圆
    for(int i = 0; i < layerNums; i++)
    {
        glBegin(GL_LINE_LOOP);
        for(int j = 0; j < circlePoints; j++)
        {
            glVertex3f(circlePointss[i][3 * j], circlePointss[i][3 * j + 1], circlePointss[i][3 * j + 2]);
        }
        glEnd();
    }
    // 画每一条连接边
    for(int i = 0; i < circlePoints; i++)
    {
        glBegin(GL_LINE_STRIP);
        for(int j = 0; j < layerNums; j++)
        {
            glVertex3f(circlePointss[j][3 * i], circlePointss[j][3 * i + 1], circlePointss[j][3 * i + 2]);
        }
        glVertex3f(centerX - radius, centerY, centerZ);
        glEnd();
    }

    glFlush();
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
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("HalfSphereLeftDown");

    glutDisplayFunc(Display);     // 显示
    glutReshapeFunc(ChangeSize);  // 根据窗口大小调整图形大小
    glutKeyboardFunc(NormalKeys); // 监听按键事件
    Initial();
    glutMainLoop();
}