#pragma warning(disable:4996)
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid MouseDrag(int x, int y);
GLvoid MouseClick(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);

GLvoid make_rect();
int i_col(int num);
GLvoid col_check();

float x1_rect[101] = { 0, };
float y1_rect[101] = { 0, };

float x2_rect[101] = { 0, };
float y2_rect[101] = { 0, };

float c_red[101] = { 0, };
float c_green[101] = { 0, };
float c_blue[101] = { 0, };

int x_curr = 0; // 클릭한 위치
int y_curr = 0;

// 클릭시 curr 값을 읽고, 드래그시 curr 인덱스의 정점을 계속 옮김
// for문에서 0-4까지 
// 겹친 것 중에서 가장 큰수(마지막에 생성된 사각형)을 찾고, 
// 반복문 밖에서 드래그 적용

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

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    make_rect();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);

    glutMouseFunc(MouseClick); // 클릭
    glutMotionFunc(MouseDrag); // 드래그
    glutKeyboardFunc(Keyboard); // 키보드

    glutMainLoop(); // 이벤트 처리
}

GLvoid drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 101; i++) {
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
    float x1 = 0.0f;
    float x2 = 0.0f;
    float y1 = 0.0f;
    float y2 = 0.0f;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x1_rect[100] = 2.0f * (float)x / X_MAX - 1.2f;
        y1_rect[100] = -(2.0f * (float)y / Y_MAX - 0.8f);
        x2_rect[100] = 2.0f * (float)x / X_MAX - 0.8f;
        y2_rect[100] = -(2.0f * (float)y / Y_MAX - 1.2f);
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        x1_rect[100] = 0;
        y1_rect[100] = 0;
        x2_rect[100] = 0;
        y2_rect[100] = 0;
    }

    x_curr = x;
    y_curr = y;

    col_check();

    drawScene();
}



GLvoid MouseDrag(int x, int y)
{
    // x, y는 좌상을 0,0으로, 우하를 원도우창 크기로 한다.
    float x1 = 0.0f;
    float x2 = 0.0f;
    float y1 = 0.0f;
    float y2 = 0.0f;

    // 드래그시 이동
    x1 = X_MAX / 2 + (x1_rect[100] * X_MAX / 2);
    x2 = X_MAX / 2 + (x2_rect[100] * X_MAX / 2);
    y1 = Y_MAX / 2 - (y1_rect[100] * Y_MAX / 2);
    y2 = Y_MAX / 2 - (y2_rect[100] * Y_MAX / 2);

    if (x1 <= x && x <= x2 && y2 <= y && y <= y1) {
        x1_rect[100] -= (x_curr - x) / (X_MAX / 2.0f);
        x2_rect[100] -= (x_curr - x) / (X_MAX / 2.0f);
        y1_rect[100] += (y_curr - y) / (Y_MAX / 2.0f);
        y2_rect[100] += (y_curr - y) / (Y_MAX / 2.0f);

        x_curr = x;
        y_curr = y;
    }
    col_check();
    drawScene();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
    if (key == 'r') {
        make_rect();
        col_check();
    }

    drawScene();

}

GLvoid make_rect()
{
    float r = 0.0f;
    for (int i = 0; i < 100; i++) {
        c_red[i] = rand() / (float)RAND_MAX;
        c_green[i] = rand() / (float)RAND_MAX;
        c_blue[i] = rand() / (float)RAND_MAX;

        r = (rand() / (float)RAND_MAX - 0.5f) * 2;

        x1_rect[i] = r - 0.05f;
        x2_rect[i] = r + 0.05f;

        r = (rand() / (float)RAND_MAX - 0.5f) * 2;

        y1_rect[i] = r - 0.05f;
        y2_rect[i] = r + 0.05f;
    }
    c_red[100] = 0.3f;
    c_green[100] = 0.3f;
    c_blue[100] = 0.3f;

    drawScene();
}

int i_col(int num)
{
    int s = 0;
    int col[4] = { 0, }; // x1, y1, x2, y2

    float r1_c[4] = { x1_rect[100] , y1_rect[100] , x2_rect[100] , y2_rect[100] }; // x1, y1, x2, y2
    float r2_c[4] = { x1_rect[num] , y1_rect[num] , x2_rect[num] , y2_rect[num] }; // x3, y3, x4, y4

    for (int i = 0; i < 4; i++) {
        if (r2_c[i % 2] < r1_c[i] && r1_c[i] < r2_c[i % 2 + 2]) {
            col[i] = 1;
        }
    }

    if (col[0] == 1 || col[2] == 1) { // r1의 x값중 하나가 침범했을 경우
        if (col[1] == 1 || col[3] == 1) { // r1의 y값중 하나가 침범했을 경우
            return 0; // 충돌
        }
    }

    for (int i = 0; i < 4; i++) {
        col[i] = 0; // 초기화
        if (r1_c[i % 2] < r2_c[i] && r2_c[i] < r1_c[i % 2 + 2]) {
            col[i] = 1;
        }
    }

    if (col[0] == 1 || col[2] == 1) { // r2의 x값중 하나가 침범했을 경우
        if (col[1] == 1 || col[3] == 1) { // r2의 y값중 하나가 침범했을 경우
            return 0; // 충돌
        }
    }

    return 1; // 비충돌
}
// 옵션 텍스트 편집기 파일 확장 - glsl

GLvoid col_check()
{
    for (int i = 0; i < 100; i++) {
        if (!i_col(i)) {
            x1_rect[i] = 0.0f;
            y1_rect[i] = 0.0f;
            x2_rect[i] = 0.0f;
            y2_rect[i] = 0.0f;
        }
    }
}

