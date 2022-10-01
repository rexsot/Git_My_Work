#pragma warning(disable: 4996)
#include <stdio.h>
#include <string.h>
#include <Windows.h>

#define MAX 1000
char str[MAX] = { 0, }; // 배열

void p_menu()
{
    printf("---파일 읽기 프로그램---\n\n\n");
    printf("---명령어---\n");
    printf("d: 문장 뒤집기\n");
    printf("e: 간격 삽입\n");
    printf("f: 간격 기준 뒤집기\n");
    printf("g: 문자 변경\n");
    printf("h: 앞뒤 동일 문자 수 출력\n");
    printf("q: 프로그램 종료\n");
    printf("\n\n명령어 입력: ");
}

void chn(char *c1, char *c2)
{
    printf("변경하고 싶은 문자: ");
    scanf("%c", &*c1);
    getchar();
    printf("바꿀 문자: ");
    scanf("%c", &*c2);
    getchar();
}

int main()
{
    char sel;
    char c1, c2;

	FILE* fp = fopen("data.txt", "r"); // 파일 읽기모드

    int d = 1; // 뒤집기 판정
    int e = 1; // 띄어쓰기 판정
    int f = 1; // 띄어쓰기 기준 뒤집기 판정
    int g = 1; // 문자 변경
    int rv = 0; // 띄어쓰기 기준 뒤집기 인덱스 좌표 계산용

    while (1)
    {
        p_menu();
        scanf("%c", &sel);
        getchar();
        system("cls");

        switch (sel)
        {
        case 'd': // 문장 뒤집기
            d *= -1;
            break;
        case 'e':
            e *= -1;
            break;
        case 'f':
            if (e == -1) { // e가 켜져있으면 f를 킨다.
                f *= -1;
            }
            else {
                e *= -1; // e가 꺼져있으면 e를 킨다.
            }
            break;
        case 'g':
            system("cls");
            g = -1;
            chn(&c1, &c2);
            break;
        case 'h':
            for (int k = 0; k < 10; k++) {
                fgets(str, MAX, fp); // 한줄마다 읽음, 초기화됨
                printf("%s: ", str);
                for (int i = 0; i < strlen(str) - 1; i++) {
                    if (str[i] == str[strlen(str) - i - 2]) {
                        printf("%c", str[i]);
                    }
                    else {
                        break;
                    }
                }
                printf("\n");
            }
            system("pause");
            system("cls");
            getchar();
            rewind(fp); // 파일 포인터 초기화
            continue;
        case 'q': // 프로그램 종료
            system("cls");
            printf("프로그램을 종료합니다.\n");
            exit(0);
        default: // 다시 입력
            printf("\n다시 입력해주세요.\n");
            system("pause");
            system("cls");
            getchar();
            continue;
        }

        for (int k = 0; k < 10; k++) {
            fgets(str, MAX, fp); // 한줄마다 읽음, 초기화됨

            if (g == -1) { // 변경이 켜져있다면
                for (int i = 0; i < strlen(str); i++)
                {
                    if (str[i] == c1)
                    {
                        str[i] = c2;
                    }
                }
            }

            for (int i = 0; i < strlen(str) - 1; i++)
            {
                if (e == -1) { // 삽입이 켜져있을때
                    if ((i) % 3 == 0) { // 4번째마다 
                        if (i != 0) {
                            printf("@@");
                        }
                    }
                }

                rv = 3 * (i / 3) + 2 - i % 3; // 2->1->0->5->4->3...

                if (f == 1) { // 띄어쓰기 뒤집기가 꺼져있을 때
                    if (d == 1) { // 뒤집기가 꺼져있을 때
                        printf("%c", str[i]);
                    }
                    else { // 뒤집기가 켜져있을 때
                        printf("%c", str[strlen(str) - i - 2]); // 줄바꿈 제거
                    }
                }
                else { // 띄어쓰기 뒤집기가 켜져있을 때
                    if (d == 1) { // 뒤집기가 꺼져있을 때
                        if (str[rv] != '\n') { // 줄바꿈이 아닐때 실행
                            printf("%c", str[rv]);
                        }
                    }
                    else { // 뒤집기가 켜져있을 때
                        printf("%c", str[strlen(str) - rv - 2]); // 줄바꿈 제거
                    }
                }
            }
                printf("\n"); // 줄바꿈 추가
        }

        printf("\n\n");
        system("pause");
        system("cls");
        g = 1; // 변경값 초기화
        rewind(fp); // 파일 포인터 초기화
    }

	fclose(fp); // 파일 닫기
	return 0;
}