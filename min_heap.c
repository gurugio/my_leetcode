#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void print_heap(int *heap, int size)
{
	for (int i = 0; i < size; i++)
		printf("%d = %d\n", i, heap[i]);
}

void add_heap(int *heap, int *size, int x)
{
	int current = *size;
	int parent;
	
	heap[current] = x;
	(*size)++;

	while (current > 0) {
		parent = (current - 1) / 2;
		if (heap[parent] > heap[current]) {
			int t = heap[parent];
			//printf("swap %d %d\n", heap[parent], heap[current]);

			heap[parent] = heap[current];
			heap[current] = t;
		        current = parent;
		} else {
			break;
		}
	}
}

int del_heap(int *heap, int *size)
{
	int current;
	int ret = heap[0];
	int left, right;
	heap[0] = heap[*size - 1];
	heap[*size - 1] = 0xfffffff;
	(*size)--;
	current = 0;
	while (current < *size) {
		left = current*2 + 1;
		if (left >= *size)
			break;
		right = current*2 + 2;
		if (right >= *size)
			heap[right] = 0xfffffff;

		//printf("%d=%d %d=%d %d=%d\n", current, heap[current], left, heap[left], right, heap[right]);
		if (heap[current] < heap[left] && heap[current] < heap[right]) {
			break;
		} else if (heap[left] <= heap[right]) { // '=' is very important: for ex) 82 25 25
			int t = heap[left];
			//printf("swap %d %d\n", heap[left], heap[current]);
			heap[left] = heap[current];
			heap[current] = t;
			current = left;
		} else if (heap[left] > heap[right]) {
			int t = heap[right];
			//printf("swap %d %d\n", heap[right], heap[current]);
			heap[right] = heap[current];
			heap[current] = t;
			current = right;
		} else {
			break;
		}
	}
	return ret;
}

int main(void)
{
	int min_heap[500] = {0,};
	int heap_size = 0;
	srand((unsigned)time(NULL));

	//int ddd[] = {79, 4, 45, 66, 26, 14, 50, 30, 73, 20, 36, 43, 38, 52, 36, 43, 16, 82, 25, 25};

	for (int i = 0; i < 500; i++) {
		int x = rand() % 10000;
		printf("add: %d\n", x);
		add_heap(min_heap, &heap_size, x);
	}
	print_heap(min_heap, heap_size);
	
	for (int i = 0; i < 500; i++) {
		int x = del_heap(min_heap, &heap_size);
		printf("del: %d\n", x);
		//print_heap(min_heap, heap_size);
	}

	for (int i = 0; i < 499; i++) {
		if (min_heap[i] > min_heap[i+1]) {
			printf("%d %d\n", min_heap[i], min_heap[i+1]);
		}
	}
	
	return 0;
}
