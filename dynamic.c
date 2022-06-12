#include <stdio.h>
#include <string.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))


void example1(void)
{
	int n;
	int i;
	int pi[] = {0,1,5,8,9,10,17,17,20,24,30};
	int result[20] = {0,};

	result[1] = 1;
	result[2] = 5;

	for (n = 3; n <= 10; n++) {
		result[n] = pi[n];
		for (i = 0; i < n; i++) {
			result[n] = MAX(result[n], pi[n - i] + result[i]);
		}
	}
	
	for (n = 0; n <= 10; n++)
		printf("%d->%d\n", n, result[n]);
}

int lcs(char *str1, int last1, char *str2, int last2)
{
	if (last1 < 0 || last2 < 0)
		return 0;
	if (str1[last1] == str2[last2])
		return lcs(str1, last1 - 1, str2, last2 - 1) + 1;
	else
		return MAX(lcs(str1, last1 - 1, str2, last2),
			   lcs(str1, last1, str2, last2 - 1));
}

void example2(void)
{
	char str1[] = "abcbdabcg";
	char str2[] = "bdcabafcg";
	printf("%d\n", lcs(str1, strlen(str1) - 1, str2, strlen(str2) - 1));
}

/* https://www.zerocho.com/category/Algorithm/post/584b979a580277001862f182 */
int num_item = 3;
int item_price[] = {60, 100, 120};
int item_weight[] = {10, 20, 30};

int max_price(int *parray, int *warray, int max_item, int max_weight)
{
	int p[10];
	int w[10];
	int i;
	int max;
	int max_index;
	
	for (i = 0; i < num_item; i++) {
		w[i] = warray[max_item - 1] + item_weight[i];
		if (w[i] > max_weight)
			p[i] = -1;
		else
			p[i] = parray[max_item - 1] + item_price[i];
		printf("p=%d\n", p[i]);
	}
	max = 0;
	max_index = 0;
	for (i = 0; i < num_item; i++) {
		if (p[i] > max) {
			max = p[i];
			max_index = i;
		}
	}
	parray[max_item] = max;
	warray[max_item] = w[max_index];
	return max;
}

void example3(void)
{
	int parray[10] = {0,};
	int warray[10] = {0,};
	int max_weight = 70;
	int max;
	int i;
	printf("%d\n", max_price(parray, warray, 1, max_weight));
	printf("%d\n", parray[1]);
	printf("%d\n", max_price(parray, warray, 2, max_weight));
	printf("%d\n", parray[2]);
	printf("%d\n", max_price(parray, warray, 3, max_weight));
	printf("%d\n", parray[3]);
	printf("%d\n", max_price(parray, warray, 4, max_weight));
	printf("%d\n", parray[4]);
	max = 0;
	for (i = 0; i <= 4; i++)
		if (parray[i] > max)
			max = parray[i];
	printf("result=%d\n", max);
}

int main(void)
{
	//example1();
	//example2();
	example3();
}
