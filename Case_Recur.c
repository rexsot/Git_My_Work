#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h> // system 함수추가

// num배열에 들어있는 수를 앞에서부터 deep만큼 읽어서, 그 수들의 모든 경우의 수를 조합해 내림차순으로 출력한다.

void case_recur(int a, int c, int num[], int data[]) // 현재 deep, 원래 deep, 
{
	if (a == 0) { // 현재 deep이 0일때, data를 원래 deep만큼 읽어서 출력
		for (int i = 0; i < c; i++) { // 원래 deep만큼 반복
			printf("%d ", data[i]); // data를 출력
		}
		printf("\n");
		return;
	}
	for (int i = 0; i < num[a - 1]; i++) { // 현재 deep이 0이상일 때, 현재 deep-1 위치의 반복수만큼 반복
		data[a - 1] = (i + 1); // 출력용 배열의 현재 deep-1번째 인덱스 위치에 값을 넣는다.(i가 0부터 시작이므로 1을 더한다)
		case_recur(a - 1, c, num, data); // 재귀
	}
}

int main()
{
	int deep = 0; // 탐색 깊이
	int sel = 0; // 배열값

	while (1) {
		printf("탐색할 깊이 입력: ");
		scanf("%d", &deep);
		if (deep < 1) { // 음수 / 0 입력시
			printf("다시 입력해주세요.\n");
			system("pause");
			system("cls");
			getchar();
			continue;
		}
		break;
	}

	int* num = (int*)malloc(sizeof(int) * deep); // 동적할당 - 입력용 배열
	int* data = (int*)malloc(sizeof(int) * deep); // 동적할당 - 출력용 배열

	for (int i = 0; i < deep; i++)
	{
		printf("%d번째 배열 입력: ", i + 1);
		scanf("%d", &sel);
		if (sel < 1) {
			printf("다시 입력해주세요.\n");
			system("pause");
			system("cls");
			getchar();
			i -= 1;
			continue;
		}
		num[i] = sel; // 입력용 배열에 값 입력
	}

	system("cls");
	case_recur(deep, deep, num, data);

	free(num); // 동적할당 해제
	free(data); // 동적할당 해제

	return 0;
}
