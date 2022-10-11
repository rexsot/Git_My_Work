#pragma warning(disable:4996)
#include<stdio.h>

int main()
{
	// 1234543212345....
	// 1234 5 432 1

	int n = 1;
	int boo = -1;

	for (int i = 0; i < 20; i++) {

		if (n == 1 || n == 5) {
			boo *= -1;
		}
		printf("%d\n", n);
		n += boo;
	}
	return 0;
}