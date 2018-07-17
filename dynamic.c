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

int main(void)
{
	//example1();
	example2();
}
