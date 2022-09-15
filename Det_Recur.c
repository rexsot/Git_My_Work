#pragma warning (disable: 4996)
#include<stdio.h>

int matrix[4][4] = 
{
	{1,1,1,1},
        {2,1,2,1},
	{1,3,2,1},
	{1,1,2,2}
};

int recur_det(int mat[4][4], int deep)
{
	if (deep <= 1) { // 깊이가 1이라면 탈출
		return mat[0][0]; 
	}

	int sum = 0; // 리턴값
	int b = 1; // 부호
	int m_mat[4][4] = {0, };

	for (int k = 0; k < deep; k++) { // 스킵할 j번째 값
		for (int i = 1; i < deep; i++) { // 여인수 전개상 첫행은 스킵
			for (int j = 0; j < deep; j++) {
				if (j < k) {
					m_mat[i - 1][j] = mat[i][j];
				}
				else if (j > k) {
					m_mat[i - 1][j-1] = mat[i][j];
				}
			}
		}
		sum += b * mat[0][k] * recur_det(m_mat, deep - 1);
		b *= -1; // 부호변경
	}
	return sum;
}

int main()
{
	int deep = 4;
	printf("행렬식: %d", recur_det(matrix, deep));
	return 0;
}
