/**
 * 绘制三维图形 右键选择框切换绘制茶壶 圆锥 球体等的线图和实体图
 * 可以使用按键和鼠标进行平移 旋转 放缩 视角调整
 * 
 * i j k l键进行旋转
 * w a s d键进行平移 不允许移出窗口
 * - =(+) 键进行图像的缩小和放大 由于观测点的固定 放大过多会导致图形观测不全
 * 鼠标左键拖动视角旋转 为了避免异常的视角 对角度进行了限制 看不全图形时可以进行缩放
 */
#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

static GLsizei iMode = 1;        // 当前状态
static GLfloat xRot = 0;         // x旋转量
static GLfloat yRot = 0;         // y旋转量
static GLfloat dx = 0;           // x平移量
static GLfloat dy = 0;           // y平移量
static GLfloat dz = 0;           // z平移量

static GLfloat scaleRatio = 1.0; // 缩放比例

static int du = 90, oldmy = -1, oldmx = -1;   // du是视点绕y轴的角度 默认y轴是上方向
static double r = 0.5f, h = 0.0f;             // r是视点绕y轴的半径 h是视点高度即在y轴上的坐标
static double hLim = 0.45f;                   // 高度限制
static double radiusPerAngle = M_PI / 180.0f; // 弧度和角度转换参数

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
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5, 1.5, -1.5, 1.5);
}

/**
 * 鼠标点击事件
 * 
 * @param button 当前鼠标按键
 * @param state 当前鼠标状态
 * @param x 当前鼠标x坐标
 * @param y 当前鼠标y坐标
 */
void Mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) // 第一次鼠标按下时 记录鼠标在窗口中的初始坐标
        oldmx = x, oldmy = y;
}

/**
 * 鼠标拖动事件
 * 
 * @param x 当前鼠标x坐标
 * @param y 当前鼠标y坐标
 */
void onMouseMove(int x, int y)
{
    du += x - oldmx;          // x轴方向的拖动控制左右旋转
    h += 0.03f * (y - oldmy); // y轴方向的拖动控制上下旋转
    if (h > hLim)
        h = hLim;             // 视点y进行限制 避免异常视角
    else if (h < -hLim)
        h = -hLim;
    oldmx = x, oldmy = y;     // 记录当前鼠标坐标为旧值 准备下一次计算差值
    glutPostRedisplay();
}

/**
 * 显示主函数
 */
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(scaleRatio, scaleRatio, scaleRatio); // 缩小放大比例
    glRotatef(xRot, 1, 0, 0);                     // x轴旋转
    glRotatef(yRot, 0, 1, 0);                     // y轴旋转
    glTranslatef(dx, dy, dz);                     // 平移 仅使能x y方向
    // 头朝上从当前视点看原点
    gluLookAt(r * cos(radiusPerAngle * du), h, r * sin(radiusPerAngle * du), 0, 0, 0, 0, 1, 0);
    switch (iMode)
    {
    case 1:
        glutWireTetrahedron();
        break;
    case 2:
        glutSolidTetrahedron();
        break;
    case 3:
        glutWireOctahedron();
        break;
    case 4:
        glutSolidOctahedron();
        break;
    case 5:
        glutWireSphere(1, 18, 18);
        break;
    case 6:
        glutSolidSphere(1, 18, 18);
        break;
    case 7:
    {
        GLfloat points[3][4] = {
            -2.0, 0, 0, 1,
            2.0, 2.0, 2.0, 1,
            -2.0, -2.0, 2.0, 1};
    
        GLfloat colors[3][4] = {
            0, 1.0, 0, 1,
            1.0, 0, 0, 1,
            0, 0, 1.0, 1};
    
        
        glLightfv(GL_LIGHT0, GL_DIFFUSE, colors[0]);
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
        glutWireTeapot(1);
        break;
    }
    case 8:
        glutSolidTeapot(1);
        break;
    case 9:
        gluSphere(obj, 1, 18, 18);
        break;
    case 10:
        gluCylinder(obj, 0.5, 0, 1, 18, 18);
        break;
    case 11:
        gluPartialDisk(obj, 0.3, 0.8, 18, 18, 30, 260);
        break;
    default:
        break;
    }
    glFlush();
}

/**
 * 处理菜单事件
 * 
 * @param value 当前菜单状态
 */
void ProcessMenu(int value)
{
    iMode = value;
    glutPostRedisplay();
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

    if (key == 'a')
        dx -= 0.01;
    if (key == 'd')
        dx += 0.01;
    if (key == 's')
        dy -= 0.01;
    if (key == 'w')
        dy += 0.01;
    if (dx <= -0.9)
        dx = -0.9;
    if (dx > 0.9)
        dx = 0.9;
    if (dy <= -0.9)
        dy = -0.9;
    if (dy > 0.9)
        dy = 0.9;

    if (key == '-')
        scaleRatio -= 0.05;
    if (key == '=')
        scaleRatio += 0.05;
    if (scaleRatio <= 0)
        scaleRatio = 0.05;
    if (scaleRatio >= 2.5)
        scaleRatio = 2.5;

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL");

    int nGlutPolyMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("REGULAR_TETRAHEDRON", 1); // 线框正四面体
    glutAddMenuEntry("SOLID_TETRAHEDRON", 2);   // 实体正四面体
    glutAddMenuEntry("REGULAR_OCTAHEDRON", 3);  // 线框正八面体
    glutAddMenuEntry("SOLID_OCTAHEDRON", 4);    // 实体正八面体

    int nGlutCurveMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("SPHERE_LOOP", 5);  // 线框球面
    glutAddMenuEntry("SPHERE_SOLID", 6); // 实体球面
    glutAddMenuEntry("TEAPOT_LOOP", 7);  // 线框茶壶
    glutAddMenuEntry("TEAPOT_SOLID", 8); // 实体茶壶

    int nGluCurveMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("SPHERE_LOOP", 9);    // 线框球面
    glutAddMenuEntry("CYLINDER_LOOP", 10); // 线框圆锥面
    glutAddMenuEntry("RING_LOOP", 11);     // 线框圆环面

    int nMainMenu = glutCreateMenu(ProcessMenu);
    glutAddSubMenu("GLUT_POLYGON", nGlutPolyMenu);    // GLUT多面体
    glutAddSubMenu("GLUT_HOOK_FACE", nGlutCurveMenu); // GLUT圆环面
    glutAddSubMenu("GLU_HOOK_FACE", nGluCurveMenu);   // GLU圆环面
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(Display);     // 显示
    glutReshapeFunc(ChangeSize);  // 根据窗口大小调整图形大小
    glutKeyboardFunc(NormalKeys); // 监听按键事件
    glutMouseFunc(Mouse);
    glutMotionFunc(onMouseMove);
    Initial();
    glutMainLoop();
}