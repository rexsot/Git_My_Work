#pragma warning(disable:4996)
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
int d = 1;

int main(int argc, char** argv)
{
    glutInit(&argc, argv); //glut 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
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
    glutKeyboardFunc(Keyboard);
    glutMainLoop(); // 이벤트 처리
}

GLvoid drawScene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void TimerFunction(int value)
{
    int num = 0;
    num = rand() % 3;
    switch (num)
    {
    case 0: glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        break;
    case 1: glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        break;
    case 2: glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        break;
    default:
        break;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
  
    if (d == 1) {
        glutTimerFunc(1000, TimerFunction, 1); // 타이머함수 재 설정
    }
    else {
        return;
    }
}
GLvoid Keyboard(unsigned char key, int x, int y)
{
    int num = 0;
    if (key == 'a') {
        num = rand() % 3;
        switch (num)
        {
        case 0: key = 'r';
            break;

        case 1: key = 'g';
            break;

        case 2: key = 'b';
            break;

        default:
            break;
        }
    }

    switch (key) {
    case 'r':
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        break; //--- 배경색을 빨강색으로 설정
    case 'g':
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        break; //--- 배경색을 초록색으로 설정
    case 'b':
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        break; //--- 배경색을 파랑색으로 설정
    case 'w':
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        break; //--- 배경색을 흰색으로 설정
    case 'k':
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        break; //--- 배경색을 검은색으로 설정
    case 't':
        d = 1;
        glutTimerFunc(100, TimerFunction, 1);
        break;
    case 's':
        d = 0;
        break;
    case 'q':
        exit(0);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

