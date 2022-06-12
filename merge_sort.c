#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge_array(int *a, int i, int m, int j)
{
	int *aux = calloc(j - i + 1, sizeof(int));
	int index = 0;
	int left = i;
	int right = m + 1;
	
	while (left <= m && right <= j) {
		if (a[left] < a[right])
			aux[index++] = a[left++];
		else
			aux[index++] = a[right++];
	}

	while (left <= m)
		aux[index++] = a[left++];
	while (right <= j)
		aux[index++] = a[right++];

	memcpy(&a[i], aux, sizeof(int) * (j - i + 1));
	free(aux);
}

void merge_sort(int *a, int i, int j)
{
	if (i > j) {
		printf("index error i=%d j=%d\n", i, j);
		exit(1);
	} else {
		printf("i=%d j=%d\n", i, j);
	}

	if (i == j) return;
	else if ((i + 1) == j) {
		if (a[i] > a[j]) {
			int t;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	} else {
		int middle = (i + j) / 2;
		merge_sort(a, i, middle);
		merge_sort(a, middle+1, j);
		merge_array(a, i, middle, j);
	}
}

int main(void)
{
	int test[] = {0,8,6,4,2,1,3,5,7,9};
	int i;
	merge_sort(test, 0, sizeof(test)/sizeof(int) - 1);
	for (i = 0; i < sizeof(test) / sizeof(int); i++) {
		printf("%d ", test[i]);
	}
	printf("\n");
	return 0;
}
