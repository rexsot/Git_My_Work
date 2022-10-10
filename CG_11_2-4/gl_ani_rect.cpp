#pragma warning(disable:4996)
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid MouseClick(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
void TimerFunction_A(int value);
void TimerFunction_I(int value);
void TimerFunction_C(int value);

int frame = 0;
int d[5] = { 0, };

// on off 스위치
int a = -1;
int i = -1;
int c = -1;

float cen_x[5] = { 0.0f, 0 };
float cen_y[5] = { 0.0f, 0 };

float x1_rect[5] = { -0.2f, 0, };
float y1_rect[5] = { -0.2f, 0, };

float x2_rect[5] = { 0.2f, 0, };
float y2_rect[5] = { 0.2f, 0, };

float c_red[5] = { 1.0f, 0.0f, 0.0f, 0.2f, 0.4f };
float c_green[5] = { 0.0f, 1.0f, 0.0f, 0.3f, 0.5f };
float c_blue[5] = { 0.0f, 0.0f, 1.0f, 0.1f, 0.9f };

int num_r = 1; // 사각형의 수

#define X_MAX 800
#define Y_MAX 800

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
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glutSwapBuffers();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMouseFunc(MouseClick); // 클릭
    glutKeyboardFunc(Keyboard); // 키보드
    glutMainLoop(); // 이벤트 처리
}

GLvoid drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    for (int i = 0; i < 5; i++) {
        glColor3f(c_red[i], c_green[i], c_blue[i]);
        glRectf(x1_rect[i], y1_rect[i], x2_rect[i], y2_rect[i]);
    }
    glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

GLvoid MouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && num_r < 5) {
        x1_rect[num_r] = 2.0f * (float)x / X_MAX - 1.2f;
        y1_rect[num_r] = - (2.0f * (float)y / Y_MAX - 0.8f);
        x2_rect[num_r] = 2.0f * (float)x / X_MAX - 0.8f;
        y2_rect[num_r] = - (2.0f * (float)y / Y_MAX - 1.2f);

        cen_x[num_r] = (x1_rect[num_r] + x2_rect[num_r]) / 2.0f;
        cen_y[num_r] = (y1_rect[num_r] + y2_rect[num_r]) / 2.0f;
        num_r++;
    }
    drawScene();
}

void TimerFunction_A(int value)
{
    // 0: + +
    // 1: + -
    // 2: - -
    // 3: - +

    if (a == 1) {
        for (int i = 0; i < num_r; i++) {
            
            switch (d[i])
            {
                case 0:
                    if (x2_rect[i] > 1.0f || y2_rect[i] > 1.0f) {
                        d[i]++;
                    }
                    else {
                        x1_rect[i] += 0.01f;
                        y1_rect[i] += 0.01f;
                        x2_rect[i] += 0.01f;
                        y2_rect[i] += 0.01f;
                    }
                    break;

                case 1:
                    if (x2_rect[i] > 1.0f || y1_rect[i] < -1.0f) {
                        d[i]++;
                    }
                    else {
                        x1_rect[i] += 0.01f;
                        y1_rect[i] -= 0.01f;
                        x2_rect[i] += 0.01f;
                        y2_rect[i] -= 0.01f;
                    }
                    break;

                case 2:
                    if (x1_rect[i] < -1.0f || y1_rect[i] < -1.0f) {
                        d[i]++;
                    }
                    else {
                        x1_rect[i] -= 0.01f;
                        y1_rect[i] -= 0.01f;
                        x2_rect[i] -= 0.01f;
                        y2_rect[i] -= 0.01f;
                    }
                    break;
                case 3:
                    if (x1_rect[i] < -1.0f || y2_rect[i] > 1.0f) {
                        d[i] = 0;
                    }
                    else {
                        x1_rect[i] -= 0.01f;
                        y1_rect[i] += 0.01f;
                        x2_rect[i] -= 0.01f;
                        y2_rect[i] += 0.01f;
                    }
                    break;
            default:
                break;
            }
        }
    }

    drawScene();

    if (a == 1) {
        glutTimerFunc(50, TimerFunction_A, 1); // 타이머함수 재 설정
    }
    else {
        return;
    }
}

void TimerFunction_I(int value)
{
    if (i == 1) {
        for (int i = 0; i < num_r; i++) {
            if (frame < 30) {
                x1_rect[i] -= 0.006f;
                y1_rect[i] -= 0.006f;
                x2_rect[i] -= 0.006f;
                y2_rect[i] -= 0.006f;
                frame++;
            }
            else if (frame < 60) {
                x1_rect[i] += 0.006f;
                y1_rect[i] -= 0.006f;
                x2_rect[i] += 0.006f;
                y2_rect[i] -= 0.006f;
                frame++;
            }
            else {
                frame = 0;
            }

        }
    }

    drawScene();

    if (i == 1) {
        glutTimerFunc(50, TimerFunction_I, 1); // 타이머함수 재 설정
    }
    else {
        return;
    }
}

void TimerFunction_C(int value)
{
    if (c == 1) {
        for (int i = 0; i < num_r; i++) {
            if (x2_rect[i] < 1.0f && y2_rect[i] < 1.0f) {
                x2_rect[i] += 0.002f;
                y2_rect[i] += 0.005f;
            }
        }
    }

    drawScene();

    if (c == 1) {
        glutTimerFunc(50, TimerFunction_C, 1); // 타이머함수 재 설정
    }
    else {
        return;
    }
}

GLvoid Keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {
    case 'a':
        a *= -1;
        glutTimerFunc(50, TimerFunction_A, 1);
        break;
    case 'i':
        i *= -1;
        glutTimerFunc(50, TimerFunction_I, 1);
        break;
    case 'c':
        c *= -1;
        glutTimerFunc(50, TimerFunction_C, 1);
        break;
    case 's':
        a = -1;
        i = -1;
        c = -1;
        break;
    case 'm':
        for (int i = 0; i < num_r; i++) {
            x1_rect[i] = cen_x[i] - 0.2f;
            y1_rect[i] = cen_y[i] - 0.2f;
            x2_rect[i] = cen_x[i] + 0.2f;
            y2_rect[i] = cen_y[i] + 0.2f;
        }
        break;
    case 'r':
        for (int i = 0; i < 5; i++) {
            x1_rect[i] = 0.0f;
            x2_rect[i] = 0.0f;
            y1_rect[i] = 0.0f;
            y2_rect[i] = 0.0f;
            cen_x[i] = 0;
            cen_y[i] = 0;
        }
        num_r = 0;
        break;
    case 'q':
        exit(0);
        break;
    default:
        break;
    }
   
    drawScene();
}