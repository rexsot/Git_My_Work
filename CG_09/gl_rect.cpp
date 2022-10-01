#pragma warning(disable:4996)
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);

float p_x = 0.5; // 사각형의 범위
float p_y = 0.5;

float c_r = 0.5; // 사각형 색
float c_g = 0.0;
float c_b = 0.0;

float b_r = 0.5; // 배경색
float b_g = 0.0;
float b_b = 0.0;

#define X_MAX 400
#define Y_MAX 400

int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv); //glut 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(X_MAX, Y_MAX);
    glutCreateWindow("Example1");

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        std::cout << "GLEW Initialized\n";
    }
    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMouseFunc(Mouse);
    glutMainLoop(); // 이벤트 처리
}

GLvoid drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(c_r, c_g, c_b);
    glRectf(-p_x, -p_y, p_x, p_y);
    glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
    float c_f; 
    // x, y는 좌상을 0,0으로, 우,하를 원도우창 크기로 한다.
    float x1 = X_MAX/2 - (p_x * X_MAX/2); // 400 - px * 200
    float x2 = X_MAX/2 + (p_x * X_MAX/2);
    float y1 = Y_MAX/2 - (p_y * Y_MAX/2);
    float y2 = Y_MAX/2 + (p_y * Y_MAX/2);


    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // 좌클릭
    {
        if (x1 <= x && x <= x2 && y1 <= y && y <= y2) { // 사각형 안
            c_f = (float)(rand() % 10) / 10;
            c_r = c_f;
            c_f = (float)(rand() % 10) / 10;
            c_g = c_f;
            c_f = (float)(rand() % 10) / 10;
            c_b = c_f;
        }
        else { // 사각형 밖
            c_f = (float)(rand() % 10) / 10;
            b_r = c_f;
            c_f = (float)(rand() % 10) / 10;
            b_g = c_f;
            c_f = (float)(rand() % 10) / 10;
            b_b = c_f;
            glClearColor(b_r, b_g, b_b, 1.0f);
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) // 우클릭, 크기 한계는 0.1-0.9
    {
        if (x1 <= x && x <= x2 && y1 <= y && y <= y2) { // 사각형 안
            if (p_x < 0.9 && p_y < 0.9) {
                p_x += 0.1f;
                p_y += 0.1f;
            }
        }
        else {
            if (p_x > 0.1 && p_y > 0.1) {
                p_x -= 0.1f;
                p_y -= 0.1f;
            }
        }
    }
    glutSwapBuffers();
}

