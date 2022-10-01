#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

// 거리: x^2 + y^2 + z^2가 가장 큰 수
// pow(x, 2)
// pow(y, 2)
// pow(z, 2)

struct list
{
	int x, y, z;
	int on;
};
// x, y, z

void p_list(struct list arr[])
{
	printf("\n\n\n");
	for (int i = 9; i >= 0; i--)
	{
		printf("%d: ", i);
		if (arr[i].on == 1) {
			printf("%d %d %d", arr[i].x, arr[i].y, arr[i].z);
		}
		printf("\n");
	}
}
// 리스트 출력






void p_s(struct list arr[])
{
	int k = 0;
	int n = 0;
	int t = 0;
	int q = 0;

	int d[10] = { 0, };
	int a[10] = { 0, };

	for (int i = 0; i < 10; i++)
	{
		if (arr[i].on == 1) {
			t++;
			d[i] = 1;
		}
	}
	
	for (int j = 0; j < t; j++) {
		k = 2147483647;
		for (int i = 0; i < 10; i++)
		{
			if (d[i] == 1) {
				if (k >= pow(arr[i].x, 2) + pow(arr[i].y, 2) + pow(arr[i].z, 2)) {
					n = i;
					k = pow(arr[i].x, 2) + pow(arr[i].y, 2) + pow(arr[i].z, 2);
				}
			}
		}
		d[n] = 0;
		a[q] = n;
		q++;
		printf("%d: (%d, %d, %d)\n", j,arr[n].x, arr[n].y, arr[n].z);
	}
}
// 내림차순 정렬


int main()
{
	struct list arr[10];

	char sel;
	int juk;
	int top = 0;
	int n = 0;
	int k = 0;
	int s = 0; // s가 켜져있는지 확인

	for (int i = 0; i < 10; i++)
	{
		arr[i].x = 0;
		arr[i].y = 0;
		arr[i].z = 0;
		arr[i].on = 0;
	}

	while (1)
	{
		scanf("%c", &sel);
		switch (sel)
		{
		case '+':
			if (arr[top].on == 0) // 현재 위치가 비어있음
			{
				scanf(" %d %d %d", &arr[top].x, &arr[top].y, &arr[top].z);
				arr[top].on = 1;
				if (top != 9) {
					top++;
				}
				else {
					top = 0;
				}
			}
			else { // 현재 위치가 차있음
				scanf(" %d %d %d", &juk, &juk, &juk);
				printf("입력 불가능!");
			}
			break;
		case '-':
			if (top != 0) {
				top--;
			}
			else {
				top = 9;
			}
			if (arr[top].on == 0) // 현재 위치가 비어있음(함수 전체가 비어있음)
			{
				printf("삭제 불가능!");
				if (top != 9) {
					top++;
				}
				else {
					top = 0;
				}
			}
			else { // 현재 위치가 차있음
				arr[top].x = 0;
				arr[top].y = 0;
				arr[top].z = 0;
				arr[top].on = 0;
			}
			break;
		case 'e': // 맨 밑에 값 삽입
			if (arr[0].on == 0) { // 맨 아래가 비어있을 경우
				scanf(" %d %d %d", &arr[0].x, &arr[0].y, &arr[0].z);
				arr[0].on = 1;
			}
			else { // 맨 아래가 차있을 경우
				if (arr[9].on == 0) // 맨위가 비어있을 경우에만 실행
				{
					for (int i = 9; i > 0; i--)
					{
						arr[i].x = arr[i - 1].x;
						arr[i].y = arr[i - 1].y;
						arr[i].z = arr[i - 1].z;
						arr[i].on = arr[i - 1].on;
					}
					scanf(" %d %d %d", &arr[0].x, &arr[0].y, &arr[0].z);
					arr[0].on = 1;
					if (top != 9) {
						top++;
					}
					else {
						top = 0;
					}
				}
				else {
					scanf(" %d %d %d", &juk, &juk, &juk);
					printf("변경 불가능!");
				}
			}
			break;
		case 'd': // 가장 아래에 있는 값 삭제
			for (int i = 0; i < 10; i++)
			{
				if (arr[i].on == 1)
				{
					arr[i].x = 0;
					arr[i].y = 0;
					arr[i].z = 0;
					arr[i].on = 0;
					break;
				}
			}
			break;
		case 'l':
			for (int i = 0; i < 10; i++)
			{
				n += arr[i].on;
			}
			printf("---리스트 길이: %d---", n);
			break;
		case 'c':
			for (int i = 0; i < 10; i++)
			{
				arr[i].x = 0;
				arr[i].y = 0;
				arr[i].z = 0;
				arr[i].on = 0;
			}
			top = 0;
			printf("---리스트 초기화---");
			break;
		case 'm':
			for (int i = 0; i < 10; i++)
			{
				n += arr[i].on;
			}
			if (n == 0)
			{
				printf("리스트가 비어있습니다!");
			}
			else {
				for (int i = 0; i < 10; i++)
				{
					if (k < pow(arr[i].x, 2) + pow(arr[i].y, 2) + pow(arr[i].z, 2)) {
						n = i;
						k = pow(arr[i].x, 2) + pow(arr[i].y, 2) + pow(arr[i].z, 2);
					}
				}
				printf("가장 먼 점: (%d, %d, %d)", arr[n].x, arr[n].y, arr[n].z);
			}
			break;
		case 'n':
			for (int i = 0; i < 10; i++)
			{
				n += arr[i].on;
			}
			if (n == 0)
			{
				printf("리스트가 비어있습니다!");
			}
			else {
				k = 2147483647;
				for (int i = 0; i < 10; i++)
				{
					if (arr[i].on == 1) {
						if (k >= pow(arr[i].x, 2) + pow(arr[i].y, 2) + pow(arr[i].z, 2)) {
							n = i;
							k = pow(arr[i].x, 2) + pow(arr[i].y, 2) + pow(arr[i].z, 2);
						}
					}
				}
				printf("가장 가까운 점: (%d, %d, %d)", arr[n].x, arr[n].y, arr[n].z);
			}
			break;
		case 's':
			if (s == 0) {
				s = 1;
			}
			else {
				s = 0;
			}
			break;
		case 'q':
			system("cls");
			printf("프로그램을 종료합니다.\n");
			exit(0);
		default:
			printf("다시 입력해주세요.\n");
			system("pause");
			system("cls");
			getchar();
			continue;
		}
		getchar();
		n = 0;
		k = 0;
		if (s == 0)
		{
			p_list(arr);
		}
		else {
			p_s(arr);
		}
		system("pause");
		system("cls");
	}
}