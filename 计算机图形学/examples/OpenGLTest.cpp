// #include <GL/gl.h>
// #include <GL/glut.h>
// #include <stdlib.h>
// // 初始化材料属性、光源属性、光照模型，打开深度缓冲区
// void init(){
//     GLfloat mat_specular [] = { 1.0, 1.0, 1.0, 1.0 };
//     GLfloat mat_shininess [] = { 50.0 };
//     GLfloat light_position [] = { 1.0, 1.0, 1.0, 0.0 };
//     glClearColor(0.0, 0.0, 0.0, 0.0);
//     glShadeModel(GL_SMOOTH);
//     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//     glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//     glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//     glEnable(GL_LIGHTING);
//     glEnable(GL_LIGHT0);
//     glEnable(GL_DEPTH_TEST);
// }
// // 调用GLUT函数，绘制一个球
// void display(){
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glutSolidSphere(1.0, 40, 50);
//     glFlush();
// }

// int main(int argc, char** argv){
//     // GLUT环境初始化
//     glutInit(&argc, argv);
//     // 显示模式初始化
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//     // 定义窗口大小
//     glutInitWindowSize(300, 300);
//     // 定义窗口位置
//     glutInitWindowPosition(100, 100);
//     // 显示窗口，窗口标题为执行函数名 
//     glutCreateWindow(argv[0]);
//     // 调用OpenGL初始化函数
//     init();
//     // 注册OpenGL绘图函数
//     glutDisplayFunc(display);
//     // 进入GLUT消息循环，开始执行程序
//     glutMainLoop();
//     return 0;
// }


#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

static int n = 20;
static GLfloat R = 0.05;
static const GLfloat PI= 3.141592653;

void draw(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
        glVertex2f(0.1, 0.1);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(0.3, 0.3);
    glEnd();

    glLineWidth(6.0);
    glLineStipple(3, 0x0F0F);
    glEnable(GL_LINE_STIPPLE);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex2f(-0.2, -0.2);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(0.3, 0.5);
    glEnd();

    // glBegin(GL_POLYGON);
    glDisable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < n; i++) {
            glVertex2f(R * cos(2 * PI / n * i), R *  sin(2 * PI / n * i));
        }
    glEnd();

    // glBegin(GL_POLYGON);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.3, -0.3);
        glVertex2f(-0.3, -0.4);
        glVertex2f(-0.4, -0.4);
        // glVertex2f(-0.5, -0.4);
        // glVertex2f(-0.5, -0.35);
        glVertex2f(-0.4, -0.3);
    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    // setting up the display RGB color model + Alpha channel = GLUT_RGBA
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    // configure window position and size
    glutInitWindowPosition(100, 25);
    glutInitWindowSize(960, 960);

    // create window
    glutCreateWindow("Hello Opengl");

    // call to the drawing function
    glutDisplayFunc(draw);

    // loop require by opengl
    glutMainLoop();
    return 0;
} 
