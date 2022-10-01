#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>

#define MAX 1000
char str[MAX] = { 0, }; // 배열

int c_num(int i)
{
	while (i > -1 && str[i] != ' ')// 음수/공백이 나올때까지 역수색
	{
		if (str[i] < 48 || str[i]> 57) return 0; // 단어 전체가 하나라도 숫자가 아니라면 0을 리턴
		i--;
	}
	return 1; // 단어 전체가 전부 숫자라면 1을 반환
}
// 단어가 전부 숫자면 1, 하나라도 아니면 0 반환

int c_cap(int i) 
{
	int l = 0;
	while (str[i] != ' ' && str[i] != '\n')// 공백/줄바꿈이 나올때까지 수색
	{
		i++;
		l++;
	}
	return l; // 거리 리턴
}
// 현 위치로부터 가장 가까운 공백/줄바꿈까지의 거리를 반환. 그 거리 동안은 대문자의 수를 세지 않음

int main()
{
	FILE* fp = fopen("data.txt", "r"); // 파일 읽기모드
	int word = 1; // 단어 수 = 연속된 공백의 수 + 1
	int num = 0; // 숫자 수
	int cap = 0; // 대문자 수
	int ig = 0; // 가장 가까운 공백/줄바꿈까지의 거리 = 대문자를 무시하고 지나갈 길이

	for (int k = 0; k< 10; k++) {
		fgets(str, MAX, fp); // 한줄마다 읽음, 초기화됨

		for (int i = 0; i < strlen(str); i++) {
			if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\n')) { // 현재 값이 공백이 아니고, 다음 값이 공백/줄바꿈일때
				// 단어 수가 아니라 연속된 공백의 수를 판별
				word++; // 단어++
			}

			if (48 <= str[i] && str[i] <= 57) { // 현재 값이 숫자일때 
				if ((str[i + 1] == ' ' || str[i + 1] == '\n')) { // 다음 값이 공백/줄바꿈일때
					num += c_num(i);
				}
			}

			if (65 <= str[i] && str[i] <= 90) { // 현재 값이 대문자일 때
				if (ig == 0){ // 무시값이 없을 때
					cap++;
					ig += c_cap(i);
				}
			}
			if (ig > 0) ig--; // 최소 0
		}
		printf("%s", str);
	}

	word -= num; // 단어로 처리된 숫자를 빼준다.

	printf("\n\nword count: %d\n", word);
	printf("number count: %d\n", num);
	printf("Capital word: %d\n", cap);

	fclose(fp); // 파일 닫기

	return 0;
}