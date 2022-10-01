#pragma warning(disable: 4996)

#include <stdio.h>
#include <Windows.h>
#include <time.h>

// 판별법 -  사각형의 점중 하나라도 다른 사각형 안에 있으면 겹침
// 
// 랜덤으로 생성된 사각형 1의 두 좌표를 조합하여 4개의 점을 만든다.
// 랜덤으로 생성된 사각형 2의 두 좌표를 조합하여 4개의 점을 만든다.
// 그후, 충돌을 체크한다.
// 
// 예) 사각형1의 점 하나가 사각형2안에 있을 때 -
// 사각형2를 침범한 사각형 1의 점은 사각형 2의 모든 점에 대해 다음이 성립된다.
// 
// 2개의 점에 대해 x값이 크고, x값이 작다.
// 2개의 점에 대해 y값이 크고, y값이 작다.
// 
// 어느 한점이라도 침범점으로 판단되면 반복을 멈추고, 비교용 변수를 초기화한뒤 충돌을 리턴
// 반복이 끝날때까지 침범점이 없다면, 비충돌을 리턴
//
// 침범점의 x좌표가 침범당한 사각형의 x좌표 사이
// 침범점의 y좌표가 침범당한 사각형의 y좌표 사이
// 두 조건 동시만족시, 침범점
// 만족하지 않을 경우, 반대 사각형도 계산
// 모두 만족하지 않을 경우, 충돌하지 않음

int r1_c[4]; // x1, y1, x2, y2
int r2_c[4]; // x3, y3, x4, y4

// 스왑
void swap(int *a, int *b)
{
    int s = *a;
    *a = *b;
    *b = s;

}

// 충돌 판별
int i_col() 
{
    int s = 0;
    int col[4] = { 0, }; // x1, y1, x2, y2

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

// 메뉴 출력
void p_menu()
{
    printf("사각형 1 이동:wasd(상좌하우)\n");
    printf("사각형 2 이동:ijkl(상좌하우)\n");
    printf("좌표한계: (0~799, 0~599)\n\n");


    printf("사각형 1: (%3d, %3d) (%3d, %3d)\n", r1_c[0], r1_c[1], r1_c[2], r1_c[3]);
  
    printf("사각형 2: (%3d, %3d) (%3d, %3d)", r2_c[0], r2_c[1], r2_c[2], r2_c[3]);
    if (i_col() == 0) {
        printf("     충돌발생");
    }
    printf("\n\n명령어 입력: ");
}

// 에러 출력
void p_err()
{
    printf("범위를 벗어납니다!\n");
}


// r1 상 y+
void s_w()
{
    if (r1_c[1] <= 600 - 50 && r1_c[3] <= 600 - 50) {
        r1_c[1] += 50;
        r1_c[3] += 50;
    }
    else {
        p_err();
    }
}

// r1 좌 x-
void s_a()
{
    if (r1_c[0] >= 50 && r1_c[2] >= 50) {
        r1_c[0] -= 50;
        r1_c[2] -= 50;
    }
    else {
        p_err();
    }
}

// r1 하 y-
void s_s()
{
    if (r1_c[1] >= 50 && r1_c[3] >= 50) {
        r1_c[1] -= 50;
        r1_c[3] -= 50;
    }
    else {
        p_err();
    }
}

// r1 우 x+
void s_d()
{
    if (r1_c[0] <= 800 - 50 && r1_c[2] <= 800 - 50) {
        r1_c[0] += 50;
        r1_c[2] += 50;
    }
    else {
        p_err();
    }
}


// r2 상 y+
void s_i()
{
    if (r2_c[1] <= 600 - 50 && r2_c[3] <= 600 - 50) {
        r2_c[1] += 50;
        r2_c[3] += 50;
    }
    else {
        p_err();
    }
}

// r2 좌 x-
void s_j()
{
    if (r2_c[0] >= 50 && r2_c[2] >= 50) {
        r2_c[0] -= 50;
        r2_c[2] -= 50;
    }
    else {
        p_err();
    }
}

// r2 하 y-
void s_k()
{
    if (r2_c[1] >= 50 && r2_c[3] >= 50) {
        r2_c[1] -= 50;
        r2_c[3] -= 50;
    }
    else {
        p_err();
    }
}

// r2 우 x+
void s_l()
{
    if (r2_c[0] <= 800 - 50 && r2_c[2] <= 800 - 50) {
        r2_c[0] += 50;
        r2_c[2] += 50;
    }
    else {
        p_err();
    }
}


int main()
{
    srand(time(NULL));
    char sel; // 선택값

    for (int i = 0; i < 4; i++) {
        // 0, 1, 0, 1
        r1_c[i] = rand() % (600 + ((i + 1) % 2 * 200)); // 800, 600
        r2_c[i] = rand() % (600 + ((i + 1) % 2 * 200));
    }
    // 정렬
    if (r1_c[0] > r1_c[2]) {
        swap(&r1_c[0], &r1_c[2]);
    }
    if (r1_c[1] > r1_c[3]) {
        swap(&r1_c[1], &r1_c[3]);
    }

    if (r2_c[0] > r2_c[2]) {
        swap(&r2_c[0], &r2_c[2]);
    }
    if (r2_c[1] > r2_c[3]) {
        swap(&r2_c[1], &r2_c[3]);
    }

    while (1) {

        p_menu();
        scanf("%c", &sel);

        switch (sel)
        {
        case 'w':
            s_w();
            break;
        case 'a':
            s_a();
            break;
        case 's':
            s_s();
            break;
        case 'd':
            s_d();
            break;
        case 'i':
            s_i();
            break;
        case 'j':
            s_j();
            break;
        case 'k':
            s_k();
            break;
        case 'l':
            s_l();
            break;
        default:
            printf("다시 입력해주세요.\n");
            break;
        }
        printf("\n");
        getchar();
    }
    return 0;
}