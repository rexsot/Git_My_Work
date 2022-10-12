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
GLvoid MouseClick(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);

int curr = -1; // 현재 삼각형
int swit = 1;

void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
void InitBuffer();

GLint vertexShader; 
GLuint fragmentShader;
GLuint shaderProgram;
GLuint VAO, VBO[2];

float vertexPosition[] = {
    0.25, 0.5, 0.0,
    0.0, 0.0, 0.0,
    0.5, 0.0, 0.0,
    0.25, 0.5, 0.0,

    -0.25, 0.5, 0.0,
    -0.5, 0.0, 0.0,
    0.0, 0.0, 0.0,
    -0.25, 0.5, 0.0,

    -0.25, 0.0, 0.0,
    -0.5, -0.5, 0.0,
    0.0, -0.5, 0.0,
    -0.25, 0.0, 0.0,

    0.25, 0.0, 0.0,
    0.5, -0.5, 0.0,
    0.0, -0.5, 0.0,
    0.25, 0.0, 0.0

};

float vertexColor[] = {
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,


    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,


    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,


    1.0, 1.0, 1.0,
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

    glutKeyboardFunc(Keyboard);
    glutMouseFunc(MouseClick);
    glutMainLoop();
}

GLvoid drawScene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    InitBuffer();

    glUseProgram(shaderProgram);
    //glBindVertexArray(VAO);

    if (swit == 1) {
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 4, 3);
        glDrawArrays(GL_TRIANGLES, 8, 3);
        glDrawArrays(GL_TRIANGLES, 12, 3);
    }
    else {
        //glDrawArrays(GL_LINES, 0, 12);
        for (int i = 0; i <= 12; i += 4) {
            glDrawArrays(GL_LINES, i, 2);
            glDrawArrays(GL_LINES, i + 1, 2);
            glDrawArrays(GL_LINES, i + 2, 2);
        }
        

    }
    glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
//GLint vertexShader;
//GLuint fragmentShader;

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

float add = 0.02f;
int n = 1;
int boo = -1;

GLvoid MouseClick(int button, int state, int x, int y)
{
    // curr은 0, 1, 2, 3을 순환한다.
    // vertexPosition[]은 x1 y1 z1 x2 y2 z2 꼴

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        curr++;

        if (n == 1 || n == 7) {
            boo *= -1;
        }
        n += boo;

        if (curr > 3) { curr = 0; }
        int i = curr * 12;

        // 중상 - p1
        vertexPosition[i] = 2.0f * (float)x / X_MAX - 1.0f;
        vertexPosition[i + 1] = -(2.0f * (float)y / Y_MAX - 1.2f + n * add);

        // 좌하 - p2
        vertexPosition[i + 3] = 2.0f * (float)x / X_MAX - 1.2f + n * add;
        vertexPosition[i + 4] = -(2.0f * (float)y / Y_MAX - 0.8f - n * add);

        // 우하 - p3
        vertexPosition[i + 6] = 2.0f * (float)x / X_MAX - 0.8f - n * add;
        vertexPosition[i + 7] = -(2.0f * (float)y / Y_MAX - 0.8f - n * add);

        vertexPosition[i + 9] = 2.0f * (float)x / X_MAX - 1.0f;
        vertexPosition[i + 10] = -(2.0f * (float)y / Y_MAX - 1.2f + n * add);


    }
    drawScene();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
    if (key == 'a') {
        swit = 1;
    }

    if (key == 'b') {
        swit = -1;
    }
    drawScene();

}

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