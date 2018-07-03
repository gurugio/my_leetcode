#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ex_1_5(char *str)
{
	int i,j;
	int m, n;
	int len = strlen(str);
	char *buf = calloc(len, sizeof(char));

	i = m = 0;
	while (str[i]) {
		j = i + 1;

		while (str[i] == str[j]) {
			j++;
		}
		buf[m++] = str[i];
		m += sprintf(&buf[m], "%d", j - i);

		i = j;
	}
	return len < m ? str : buf;
}

int set_row[10];
int set_col[10];

void ex_1_7(int (*mat)[5], int row, int col)
{
	int i, j;
	int index = 0;

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (mat[i][j] == 0) {
				set_row[index] = i;
				set_col[index] = j;
				index++;
			}
		}
	}
	while (--index >= 0) {
		printf("%d %d\n", set_row[index], set_col[index]);
		for (i = 0; i < col; i++)
			mat[set_row[index]][i] = 0;
		for (i = 0; i < row; i++)
			mat[i][set_col[index]] = 0;
	}
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}

int main(void)
{
	printf("%s\n", ex_1_5("abcdddddd"));

	int matrix[3][5] = {
		{1,    2,  3,  4,  5},
		{11,  22,  0, 44, 55},
		{111,222,333,  0,555}};
	printf("%p\n", matrix);
	ex_1_7(matrix, 3, 5);
	
	return 0;
}
