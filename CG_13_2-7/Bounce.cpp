// glew32.lib freeglut.lib
// 파일 -> 새로만들기 -> 파일 -> c++ -> glsl파일 만들기
#pragma warning(disable:4996)

#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#define X_MAX 800
#define Y_MAX 800

char* filetobuf(const char* file);
GLvoid drawScene();
GLvoid Reshape(int w, int h);
//GLvoid MouseClick(int button, int state, int x, int y);
//GLvoid Keyboard(unsigned char key, int x, int y);

void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
void InitBuffer();

GLint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;
GLuint VAO, VBO[2];
void TimerFunction_A(int value);

float vertexPosition[] = {
    0.25, 0.8, 0.0,
    0.0, 0.3, 0.0,
    0.5, 0.3, 0.0,

    -0.25, 0.5, 0.0,
    -0.5, 0.0, 0.0,
    0.0, 0.0, 0.0,

    -0.25, 0.0, 0.0,
    -0.5, -0.5, 0.0,
    0.0, -0.5, 0.0,

    0.25, 0.0, 0.0,
    0.0, -0.5, 0.0,
    0.5, -0.5, 0.0
};

float vertexColor[] = {
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,

    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,

    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,

    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0

};

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glGenBuffers(2, VBO);

    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);

    make_vertexShaders();
    make_fragmentShaders();
    make_shaderProgram();
    glutTimerFunc(50, TimerFunction_A, 1);
    //glutKeyboardFunc(Keyboard);
    //glutMouseFunc(MouseClick);
    glutMainLoop();
}

GLvoid drawScene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    InitBuffer();

    glUseProgram(shaderProgram);
  
    glDrawArrays(GL_TRIANGLES, 0, 12);
   
    
    glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

GLchar* vertexSource, * fragmentSource; 

GLvoid InitBuffer()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColor), vertexColor, GL_STREAM_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

}


int a = 1; // 스위치
int d[4] = { 0, 2, 2, 3}; // 방향값

float d_x[4] = {0.9f, 1.2f, 0.8f, 0.3f}; // 보정치 x
float d_y[4] = {1.0f, 0.7f, 1.3f, 1.2f}; // 보정치 y


void TimerFunction_A(int value)
{
    // 0: + +
    // 1: + -
    // 2: - -
    // 3: - +
    
    // 중상 - p1
    //vertexPosition[i*9] = 2.0f * (float)x / X_MAX - 1.0f;
    //vertexPosition[i*9 + 1] = -(2.0f * (float)y / Y_MAX - 1.2f);

    // 좌하 - p2
    //vertexPosition[i*9 + 3] = 2.0f * (float)x / X_MAX - 1.2f;
    //vertexPosition[i*9 + 4] = -(2.0f * (float)y / Y_MAX - 0.8f);

    // 우하 - p3
    //vertexPosition[i*9 + 6] = 2.0f * (float)x / X_MAX - 0.8f;
    //vertexPosition[i*9 + 7] = -(2.0f * (float)y / Y_MAX - 0.8f);

    if (a == 1) {
        for (int i = 0; i < 4; i++) { // i = n번째 사각형

            switch (d[i]) // 방향
            {
            case 0:
                if (vertexPosition[i * 9 + 3] > 1.0f || vertexPosition[i * 9 + 1] > 1.0f) { // 판단 기준 - 좌상(진행방향기준)
                    d[i]++;
                    // 중상 -> 우중
                    // 좌하 -> 좌상
                    // 우하 -> 좌하
                    vertexPosition[i * 9] = vertexPosition[i * 9 + 6];
                    vertexPosition[i * 9 + 6] = vertexPosition[i * 9 + 3];

                    vertexPosition[i * 9 + 4] = vertexPosition[i * 9 + 1];
                    vertexPosition[i * 9 + 1] = (vertexPosition[i * 9 + 1] + vertexPosition[i * 9 + 7]) / 2.0f;

                }
                else {
                    //x1_rect[i] += d_x[i] * 0.01f;
                    //y1_rect[i] += d_y[i] * 0.01f;
                    //x2_rect[i] += d_x[i] * 0.01f;
                    //y2_rect[i] += d_y[i] * 0.01f;

                    vertexPosition[i * 9] += d_x[i] * 0.01f; // x1 - 중
                    vertexPosition[i * 9 + 3] += d_x[i] * 0.01f; // x2 - 좌
                    vertexPosition[i * 9 + 6] += d_x[i] * 0.01f; // x3 - 우

                    vertexPosition[i * 9 + 1] += d_x[i] * 0.01f; // y1 - 상
                    vertexPosition[i * 9 + 4] += d_x[i] * 0.01f; // y2 - 하
                    vertexPosition[i * 9 + 7] += d_x[i] * 0.01f; // y3 - 하
                }
                break;

            case 1:
                if (vertexPosition[i * 9] > 1.0f || vertexPosition[i * 9 + 1] < -1.0f) { // 우중
                    d[i]++;
                    // 우중 -> 중하
                    // 좌상 -> 좌상
                    // 좌하 -> 우상
                    vertexPosition[i * 9 + 6] = vertexPosition[i * 9];
                    vertexPosition[i * 9] = (vertexPosition[i * 9] + vertexPosition[i * 9 + 3]) / 2.0f;

                    vertexPosition[i * 9 + 1] = vertexPosition[i * 9 + 7];
                    vertexPosition[i * 9 + 7] = vertexPosition[i * 9 + 4];

                }
                else {
                    vertexPosition[i * 9] += d_x[i] * 0.01f; // x1 - 우
                    vertexPosition[i * 9 + 3] += d_x[i] * 0.01f; // x2 - 좌
                    vertexPosition[i * 9 + 6] += d_x[i] * 0.01f; // x3 - 좌

                    vertexPosition[i * 9 + 1] -= d_x[i] * 0.01f; // y1 - 중
                    vertexPosition[i * 9 + 4] -= d_x[i] * 0.01f; // y2 - 상
                    vertexPosition[i * 9 + 7] -= d_x[i] * 0.01f; // y3 - 하

                    //x1_rect[i] += d_x[i] * 0.01f;
                    //y1_rect[i] -= d_y[i] * 0.01f;
                    //x2_rect[i] += d_x[i] * 0.01f;
                    //y2_rect[i] -= d_y[i] * 0.01f;
                }
                break;

            case 2:
                if (vertexPosition[i * 9] < -1.0f || vertexPosition[i * 9 + 1] < -1.0f) { // 중하
                    d[i]++;
                    // 중하 -> 좌중
                    // 좌상 -> 우상
                    // 우상 -> 우하
                    vertexPosition[i * 9] = vertexPosition[i * 9 + 3];
                    vertexPosition[i * 9 + 3] = vertexPosition[i * 9 + 6];

                    vertexPosition[i * 9 + 7] = vertexPosition[i * 9 + 1];
                    vertexPosition[i * 9 + 1] = (vertexPosition[i * 9 + 1] + vertexPosition[i * 9 + 4]) / 2.0f;
                }
                else {
                    vertexPosition[i * 9] -= d_x[i] * 0.01f; // x1 - 중
                    vertexPosition[i * 9 + 3] -= d_x[i] * 0.01f; // x2 - 좌
                    vertexPosition[i * 9 + 6] -= d_x[i] * 0.01f; // x3 - 우

                    vertexPosition[i * 9 + 1] -= d_x[i] * 0.01f; // y1 - 하
                    vertexPosition[i * 9 + 4] -= d_x[i] * 0.01f; // y2 - 상
                    vertexPosition[i * 9 + 7] -= d_x[i] * 0.01f; // y3 - 상

                    //x1_rect[i] -= d_x[i] * 0.01f;
                    //y1_rect[i] -= d_y[i] * 0.01f;
                    //x2_rect[i] -= d_x[i] * 0.01f;
                    //y2_rect[i] -= d_y[i] * 0.01f;
                }
                break;
            case 3:
                if (vertexPosition[i * 9] < -1.0f || vertexPosition[i * 9 + 1] > 1.0f) { // 좌중
                    d[i] = 0;
                    // 좌중 -> 중상
                    // 우상 -> 우하
                    // 우하 -> 좌하
                    vertexPosition[i * 9 + 6] = vertexPosition[i * 9];
                    vertexPosition[i * 9] = (vertexPosition[i * 9] + vertexPosition[i * 9 + 3]) / 2.0f;
                    
                    vertexPosition[i * 9 + 1] = vertexPosition[i * 9 + 4];
                    vertexPosition[i * 9 + 4] = vertexPosition[i * 9 + 7];
                }
                else {
                    vertexPosition[i * 9] -= d_x[i] * 0.01f; // x1 - 좌
                    vertexPosition[i * 9 + 3] -= d_x[i] * 0.01f; // x2 - 우
                    vertexPosition[i * 9 + 6] -= d_x[i] * 0.01f; // x3 - 우

                    vertexPosition[i * 9 + 1] += d_x[i] * 0.01f; // y1 - 중
                    vertexPosition[i * 9 + 4] += d_x[i] * 0.01f; // y2 - 상
                    vertexPosition[i * 9 + 7] += d_x[i] * 0.01f; // y3 - 하

                    //x1_rect[i] -= d_x[i] * 0.01f;
                    //y1_rect[i] += d_y[i] * 0.01f;
                    //x2_rect[i] -= d_x[i] * 0.01f;
                    //y2_rect[i] += d_y[i] * 0.01f;
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

//GLvoid MouseClick(int button, int state, int x, int y)
//{
//    // curr은 0, 1, 2, 3을 순환한다.
//    // vertexPosition[]은 x1 y1 z1 x2 y2 z2 꼴
//
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        curr++;
//
//        if (curr > 3) { curr = 0; }
//        int i = curr * 9;
//
//        // 중상 - p1
//        vertexPosition[i] = 2.0f * (float)x / X_MAX - 1.0f;
//        vertexPosition[i + 1] = -(2.0f * (float)y / Y_MAX - 1.2f);
//
//        // 좌하 - p2
//        vertexPosition[i + 3] = 2.0f * (float)x / X_MAX - 1.2f;
//        vertexPosition[i + 4] = -(2.0f * (float)y / Y_MAX - 0.8f);
//
//        // 우하 - p3
//        vertexPosition[i + 6] = 2.0f * (float)x / X_MAX - 0.8f;
//        vertexPosition[i + 7] = -(2.0f * (float)y / Y_MAX - 0.8f);
//    }
//    drawScene();
//}

//GLvoid Keyboard(unsigned char key, int x, int y)
//{
//    if (key == 'a') {
//        swit = 1;
//    }
//
//    if (key == 'b') {
//        swit = -1;
//    }
//    drawScene();
//}

void make_vertexShaders()
{
    vertexSource = filetobuf("vertex.glsl");
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
    glCompileShader(vertexShader);


    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
        return;
    }
}

void make_fragmentShaders()
{
    fragmentSource = filetobuf("fragment.glsl");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
    glCompileShader(fragmentShader);



    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
        return;
    }
}

void make_shaderProgram()
{
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLint result;
    GLchar errorLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, errorLog);
        std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
        return;
    }
    glUseProgram(shaderProgram);
}

char* filetobuf(const char* file)
{
    FILE* fptr;
    long length;
    char* buf;

    fptr = fopen(file, "rb");
    if (!fptr)
        return NULL;
    fseek(fptr, 0, SEEK_END);
    length = ftell(fptr);
    buf = (char*)malloc(length + 1);
    fseek(fptr, 0, SEEK_SET);
    fread(buf, length, 1, fptr);
    fclose(fptr);
    buf[length] = 0;

    return buf;
}