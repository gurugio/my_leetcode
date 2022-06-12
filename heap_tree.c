#include <stdio.h>
#include <stdlib.h>

struct heap {
	int *array;
	int size;
};

void heap_insert(struct heap *heap, int val)
{
	int cur = heap->size;
	int parent;
	
	heap->array[cur] = val;
	heap->size++;

	while (cur != 0) {
		parent = (cur - 1) / 2;
		if (heap->array[cur] < heap->array[parent]) {
			int t = heap->array[cur];
			//printf("swap %d %d\n", cur, parent);
			heap->array[cur] = heap->array[parent];
			heap->array[parent] = t;
			cur = parent;
		} else
			break;
	}

	if (heap->array[cur] < heap->array[parent]) {
		int t = heap->array[cur];
		heap->array[cur] = heap->array[parent];
		heap->array[parent] = t;
	}	
}

int heap_delete(struct heap *heap)
{
	int ret = heap->array[0];
	int parent = 0;
	int left, right, left_val, right_val, cur_val;
	
	heap->array[0] = heap->array[--heap->size];
	
	while (1) {
		left = (parent * 2) + 1;
		if (left < heap->size)
			left_val = heap->array[left];
		else
			break;

		right = (parent * 2) + 2;
		if (right < heap->size)
			right_val = heap->array[right];
		else
			right_val = 0x7fffffff;

		cur_val = heap->array[parent];
		if (cur_val > left_val && right_val >= left_val) {
			int t = heap->array[parent];
			heap->array[parent] = heap->array[left];
			heap->array[left] = t;
			parent = left;
		} else if (cur_val > right_val && left_val >= right_val) {
			int t = heap->array[parent];
			heap->array[parent] = heap->array[right];
			heap->array[right] = t;
			parent = right;
		} else
			break;
	}
	return ret;
}

void print_heap(struct heap *heap)
{
	int i;
	for (i = 0; i < heap->size; i++)
		printf("%d ", heap->array[i]);
	printf("\n");
}

int main(void)
{
	struct heap test_heap;
	int i;
	test_heap.array = calloc(100, sizeof(int));
	test_heap.size = 0;

	/* test_heap.array[0] = 10; */
	/* test_heap.size++; */
	/* test_heap.array[1] = 30; */
	/* test_heap.size++; */
	/* test_heap.array[2] = 50; */
	/* test_heap.size++; */
	/* test_heap.array[3] = 70; */
	/* test_heap.size++; */

	srand(time(NULL));

	for (i = 0; i < 10; i++) {
		heap_insert(&test_heap, rand() % 100);
		print_heap(&test_heap);
	}

	for (i = 0; i < 10; i++) {
		heap_delete(&test_heap);
		print_heap(&test_heap);
	}

	return 0;
}
