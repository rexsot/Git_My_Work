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

float x1_rect[5] = { -0.2f, 0,};
float y1_rect[5] = { -0.2f, 0,};

float x2_rect[5] = { 0.2f, 0,};
float y2_rect[5] = { 0.2f, 0, };

float c_red[5] = { 1.0f, 0.0f, 0.0f, 0.2f, 0.4f };
float c_green[5] = { 0.0f, 1.0f, 0.0f, 0.3f, 0.5f };
float c_blue[5] = { 0.0f, 0.0f, 1.0f, 0.1f, 0.9f };

int curr = 0; // 겹쳐있는 사각형중 가장 작은 값
int num_r = 1; // 사각형의 수
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
    // x, y는 좌상을 0,0으로, 우하를 원도우창 크기로 한다.
    float x1 = 0.0f;
    float x2 = 0.0f;
    float y1 = 0.0f;
    float y2 = 0.0f;

    for (int i = 0; i < 5; i++) // 겹친 값중 가장 마지막값 찾기
    {
        x1 = X_MAX / 2 + (x1_rect[i] * X_MAX / 2); // 200 - x1 * 200
        x2 = X_MAX / 2 + (x2_rect[i] * X_MAX / 2);
        y1 = Y_MAX / 2 - (y1_rect[i] * Y_MAX / 2); // y값의 좌표를 뒤집는다.
        y2 = Y_MAX / 2 - (y2_rect[i] * Y_MAX / 2);
        if (x1 <= x && x <= x2 && y2 <= y && y <= y1) { // y의 대소비교를 뒤집는다.
            curr = i;
            x_curr = x;
            y_curr = y;
        }
    }
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
    x1 = X_MAX / 2 + (x1_rect[curr] * X_MAX / 2);
    x2 = X_MAX / 2 + (x2_rect[curr] * X_MAX / 2);
    y1 = Y_MAX / 2 - (y1_rect[curr] * Y_MAX / 2); 
    y2 = Y_MAX / 2 - (y2_rect[curr] * Y_MAX / 2);

    if (x1 <= x && x <= x2 && y2 <= y && y <= y1) {
        //printf("in - %d\n", curr);
       
        x1_rect[curr] -= (x_curr - x) / (X_MAX / 2.0f);
        x2_rect[curr] -= (x_curr - x) / (X_MAX / 2.0f);
        y1_rect[curr] += (y_curr - y) / (Y_MAX / 2.0f);
        y2_rect[curr] += (y_curr - y) / (Y_MAX / 2.0f);

        x_curr = x;
        y_curr = y;
    }
    drawScene();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
    if (key == 'a' && num_r < 5) {
        x1_rect[num_r] = -0.2f;
        y1_rect[num_r] = -0.2f;
        x2_rect[num_r] = 0.2f;
        y2_rect[num_r] = 0.2f;
        num_r++;
    }
    drawScene();
}