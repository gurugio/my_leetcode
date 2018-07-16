#include <stdio.h>

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

int main(void)
{
	example1();
}
