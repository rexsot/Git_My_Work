#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int matrix1[4][4];
int matrix2[4][4];

void menu()
{
    printf("---행렬 프로그램---\n\n\n");
    printf("---명령어---\n");
    printf("m: 행렬곱 출력\n");
    printf("a: 행렬합 출력\n");
    printf("d: 행렬차 출력\n");
    printf("r: 행렬식 출력\n");
    printf("t: 전치행렬 출력\n");
    printf("h: 행렬확장후 행렬식 출력\n");
    printf("s: 행렬 재설정\n");
    printf("q: 프로그램 종료\n");
    printf("\n\n명령어 입력: ");
}

int mul(int i, int j, int m1)
{
    int r = 0;
    for (int k = 0; k < m1; k++)
    {
        r += matrix1[i][k] * matrix2[k][j];
    }
    return r;
}
// 행렬곱 연산

void p_mul(int m1)
{
    printf("---두 행렬의 곱---\n\n");

    for (int i = 0; i < m1; i++) {
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", matrix1[i][j]);
        }
        printf("|");
        if (i == 1) {
            printf(" x ");
        }
        else
        {
            printf("   ");
        }
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", matrix2[i][j]);
        }
        printf("|");
        if (i == 1) {
            printf(" = ");
        }
        else
        {
            printf("   ");
        }
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", mul(i, j, m1));
        }
        printf("|\n");
    }
    printf("\n");
}
// 행렬곱 출력

void add(int m1)
{
    printf("---두 행렬의 합---\n\n");

    for (int i = 0; i < m1; i++) {
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", matrix1[i][j]);
        }
        printf("|");
        if (i == 1) {
            printf(" + ");
        }
        else
        {
            printf("   ");
        }
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", matrix2[i][j]);
        }
        printf("|");
        if (i == 1) {
            printf(" = ");
        }
        else
        {
            printf("   ");
        }
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", matrix1[i][j] + matrix2[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}
// 행렬합 연산/출력

void sub(int m1)
{
    printf("---두 행렬의 차---\n\n");

    for (int i = 0; i < m1; i++) {
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%2d ", matrix1[i][j]);
        }
        printf(" |");
        if (i == 1) {
            printf(" - ");
        }
        else
        {
            printf("   ");
        }
        printf(" | ");
        for (int j = 0; j < m1; j++)
        {
            printf("%2d ", matrix2[i][j]);
        }
        printf(" |");
        if (i == 1) {
            printf(" = ");
        }
        else
        {
            printf("   ");
        }
        printf(" | ");
        for (int j = 0; j < m1; j++)
        {
            printf("%2d ", matrix1[i][j] - matrix2[i][j]);
        }
        printf(" |\n");
    }
    printf("\n");
}
// 행렬차 연산/출력

int det(int mat[4][4], int deep)
{
    if (deep <= 1) { // 깊이가 1이라면 탈출
        return mat[0][0];
    }
    int sum = 0; // 리턴값
    int b = 1; // 부호
    int m_mat[4][4] = { 0, };

    for (int k = 0; k < deep; k++) { // 스킵할 j번째 값
        for (int i = 1; i < deep; i++) { // 여인수 전개상 첫행은 스킵
            for (int j = 0; j < deep; j++) {
                if (j < k) {
                    m_mat[i - 1][j] = mat[i][j];
                }
                else if (j > k) {
                    m_mat[i - 1][j - 1] = mat[i][j];
                }
            }
        }
        sum += b * mat[0][k] * det(m_mat, deep - 1);
        b *= -1; // 부호변경
    }
    return sum;
}
// 행렬식 연산

void p_det(int m1)
{
    printf("---두 행렬의 행렬식---\n\n");

    for (int i = 0; i < m1; i++) {
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", matrix1[i][j]);
        }
        printf("|");
       
        if (i == 1) {
            printf(" = %2d ", det(matrix1, m1));
        }
        else
        {
            printf("      ");
        }


        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", matrix2[i][j]);
        }
        printf("|");

         if (i == 1) {
            printf(" = %2d ", det(matrix2, m1));
        }
        else
        {
            printf("      ");
        }
        printf("\n");
    }
    printf("\n");
}
// 행렬식 출력

void trn(int m1)
{
    printf("---두 행렬의 전치행렬---\n\n");
    
    int m_mat1[4][4] = {0, };
    int m_mat2[4][4] = { 0, };

    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < m1; j++) {
            m_mat1[i][j] = matrix1[i][j];
            m_mat2[i][j] = matrix2[i][j];
        }
    }

    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < m1; j++) {
            matrix1[i][j] = m_mat1[j][i];
            matrix2[i][j] = m_mat2[j][i];
        }
    }
    // 원본은 뒤집힘, 복사본이 원본
    for (int i = 0; i < m1; i++) {
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", m_mat1[i][j]);
        }
        printf("|");
        if (i == 1) {
            printf(" -> ");
        }
        else
        {
            printf("    ");
        }
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", matrix1[i][j]);
        }
        printf("|");
        
        if (i == 1) {
            printf(" = %2d ", det(matrix1, m1));
        }
        else
        {
            printf("      ");
        }

        printf("   | ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", m_mat2[i][j]);
        }
        printf("|");
        if (i == 1) {
            printf(" -> ");
        }
        else
        {
            printf("    ");
        }
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", matrix2[i][j]);
        }
        printf("|");

        if (i == 1) {
            printf(" = %2d ", det(matrix2, m1));
        }
        else
        {
            printf("      ");
        }
        printf("\n");
    }
    printf("\n");
}
// 전치행렬 연산/출력

void chn(int *m1)
{
    if (*m1 == 4) {
        printf("---이미 확장되었습니다.---\n\n");
        return;
    }
  
    *m1 = 4;

    for (int i = 0; i < *m1; i++) {

        if (i != 3) {
            printf("| ");
            for (int j = 0; j < *m1-1; j++)
            {
                printf("%d ", matrix1[i][j]);
            }
            printf("|");
        }
        else
        {
            printf("         ");
        }

        if (i == 1) {
            printf(" -> ");
        }
        else
        {
            printf("    ");
        }


        printf("| ");
        for (int j = 0; j < *m1; j++)
        {
            printf("%d ", matrix1[i][j]);
        }
        printf("|");

        if (i == 1) {
            printf(" = %2d ", det(matrix1, *m1));
        }
        else
        {
            printf("      ");
        }


        if (i != 3) {
            printf("| ");
            for (int j = 0; j < *m1-1; j++)
            {
                printf("%d ", matrix2[i][j]);
            }
            printf("|");
        }
        else
        {
            printf("         ");
        }

        if (i == 1) {
            printf(" -> ");
        }
        else
        {
            printf("    ");
        }

        printf("| ");
        for (int j = 0; j < *m1; j++)
        {
            printf("%d ", matrix2[i][j]);
        }
        printf("|");

        if (i == 1) {
            printf(" = %2d ", det(matrix2, *m1));
        }
        else
        {
            printf("      ");
        }
        printf("\n");
    }
    printf("\n");


}
// 행렬확장 연산/출력

void seed(int m1)
{
    printf("---두 행렬의 재설정---\n\n");

    int m_mat1[4][4] = { 0, };
    int m_mat2[4][4] = { 0, };

    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < m1; j++) {
            m_mat1[i][j] = matrix1[i][j];
            m_mat2[i][j] = matrix2[i][j];
        }
    }

    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < m1; j++) {
            matrix1[i][j] = rand() % 3;
            matrix2[i][j] = rand() % 3;
        }
    }
    // 원본은 재설정, 복사본이 원본
    for (int i = 0; i < m1; i++) {
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", m_mat1[i][j]);
        }
        printf("|");
        if (i == 1) {
            printf(" -> ");
        }
        else
        {
            printf("    ");
        }
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", matrix1[i][j]);
        }
        printf("|");
        printf("   | ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", m_mat2[i][j]);
        }
        printf("|");
        if (i == 1) {
            printf(" -> ");
        }
        else
        {
            printf("    ");
        }
        printf("| ");
        for (int j = 0; j < m1; j++)
        {
            printf("%d ", matrix2[i][j]);
        }
        printf("|");
        printf("\n");
    }
    printf("\n");
}
// 행렬 재설정

int main()
{
    srand(time(NULL));
    int m1 = 3; // 3*3일때 3, 4*4일때 4 
    char sel; // 선택값

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        {
            matrix1[i][j] = rand() % 3;
            matrix2[i][j] = rand() % 3;
        }
    }
    matrix1[3][3] = 1;
    matrix2[3][3] = 1;

    while (1)
    {
        menu();
        scanf("%c", &sel);
        system("cls");

        switch (sel)
        {
        case 'm':
            p_mul(m1);
            break;
        case 'a':
            add(m1);
            break;
        case 'd':
            sub(m1);
            break;
        case 'r':
            p_det(m1);
            break;
        case 't':
            trn(m1);
            break;
        case 'h':
            chn(&m1);
            break;
        case 's':
            seed(m1);
            break;
        case 'q':
            system("cls");
            printf("프로그램을 종료합니다.\n");
            exit(0);
        default:
            printf("\n다시 입력해주세요.\n");
            break;
        }
        getchar();
        system("pause");
        system("cls");
    }
    return 0;
}