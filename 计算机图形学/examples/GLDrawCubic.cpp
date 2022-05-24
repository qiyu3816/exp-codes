#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

// 立方体八顶点
static const GLfloat vertex_list[][3] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f
};
static const GLint index_list[][4] = { // 需要使用的顶点序号 六个面 一个面四点
    0, 2, 3, 1,
    0, 4, 6, 2,
    0, 1, 5, 4,
    4, 5, 7, 6,
    1, 3, 7, 5,
    2, 6, 7, 3,
};

void draw(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // 画立方体
    glFrontFace(GL_CCW); //逆时针
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
        for(int i = 0; i < 6; i++)
            for(int j = 0; j < 4; j++)
                glVertex3fv(vertex_list[index_list[i][j]]);
    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    // setting up the display RGB color model + Alpha channel = GLUT_RGBA
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_SINGLE);

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

