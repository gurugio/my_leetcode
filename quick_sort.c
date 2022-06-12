#include <stdio.h>
#include <stdlib.h>

void quick(int *a, int start, int end)
{
	int i = start + 1;
	int j = end;
	int lo = start;
	int t;

	if (start >= end)
		return;

	while (1) {
		while (a[i] < a[lo])
			i++;
		while (a[j] > a[lo])
			j--;
		if (i > j)
			break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
		printf("swap %d %d\n", i, j);
	}

	t = a[lo];
	a[lo] = a[j];
	a[j] = t;
	printf("swap %d %d\n", lo, j);

	{
		int m;
		printf("temp(%d,%d):", start, end);
		for (m = start; m <= end; m++)
			printf("%d ", a[m]);
		printf("\n");
	}
	
	quick(a, start, j - 1);
	quick(a, j + 1, end);
}

int main(void)
{
	int test[] = {10,4,7,9,5,2,1,3,6};
	//int test[] = {5,9,7,6};
	int i;
	quick(test, 0, sizeof(test)/sizeof(int) - 1);
	for (i = 0; i < sizeof(test)/sizeof(int); i++)
		printf("%d ", test[i]);
	printf("\n");
	return 0;
}
