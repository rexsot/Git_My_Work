#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

// 메인 배열
int arr[4][4];

// 공개 여부, 1일때 공개
int open[4][4];


void p_arr()
{
    printf("  a b c d\n");
    for (int i = 0; i < 4; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 4; j++) {

            if (open[i][j] == 0) { // 비공개라면 *출력
                printf("* ");
                continue;
            }

            switch (arr[i][j])
            {
            case 1:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), arr[i][j]);
                printf("A ");
                break;
            case 2:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), arr[i][j]);
                printf("B ");
                break;
            case 3:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), arr[i][j]);
                printf("C ");
                break;
            case 4:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), arr[i][j]);
                printf("D ");
                break;
            case 5:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), arr[i][j]);
                printf("E ");
                break;
            case 6:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), arr[i][j]);
                printf("F ");
                break;
            case 7:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), arr[i][j]);
                printf("G ");
                break;
            case 8:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), arr[i][j]);
                printf("H ");
                break;
            default:
                break;
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        printf("\n");
    }
}


int main()
{
    int score = 0; // 16이 되면 게임 종료
    int p1 = 0;
    int p2 = 0;
    int num = 0;
    int num2 = 0;

    char ch;
    char ch2;
    char jnk;

    int chance = 5;

    srand(time(NULL));

    for (int i = 1; i < 9; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            p1 = rand() % 4;
            p2 = rand() % 4;
            if (arr[p1][p2] == 0) {
                arr[p1][p2] = i;
            }
            else {
                j--;
                continue;
            }
        }
    }

    while (1)
    {
        p_arr();
        printf("남은 기회: %d\n", chance);
        printf("입력1: ");
        scanf("%c%d", &ch, &num);

        scanf("%c", &jnk);

        switch (ch)
        {
        case 'a':
            open[num - 1][0] = 1;
            p1 = 0;
            break;
        case 'b':
            open[num - 1][1] = 1;
            p1 = 1;
            break;

        case 'c':
            open[num - 1][2] = 1;
            p1 = 2;
            break;

        case 'd':
            open[num - 1][3] = 1;
            p1 = 3;
            break;

        default:
            printf("다시 입력해주세요.");
            break;
        }

        printf("입력2: ");
        scanf("%c%d", &ch2, &num2);
        scanf("%c", &jnk);


        switch (ch2)
        {
        case 'a':
            open[num2 - 1][0] = 1;
            p2 = 0;
            break;

        case 'b':
            open[num2 - 1][1] = 1;
            p2 = 1;
            break;

        case 'c':
            open[num2 - 1][2] = 1;
            p2 = 2;
            break;

        case 'd':
            open[num2 - 1][3] = 1;
            p2 = 3;
            break;

        default:
            printf("다시 입력해주세요.");
            break;
        }

        p_arr();

        if ((arr[num - 1][p1]) != (arr[num2 - 1][p2])) {
            printf("오답입니다.\n");
            chance--;
            open[num - 1][p1] = 0;
            open[num2 - 1][p2] = 0;
            Sleep(2000);
        }
        else {
            printf("정답입니다!\n");
            score++;
            system("pause");
        }
        system("cls");
        if (chance == 0 || score == 8) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    open[i][j] = 1;
                }
            }
            p_arr();
            printf("게임 종료\n");
            printf("점수: %d\n", score + chance);
            system("pause");
            break;
        }
    }

    return 0;
}