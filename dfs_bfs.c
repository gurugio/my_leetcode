#include <stdio.h>
#include <time.h>
#include <stdlib.h>



struct queue
{
	int *data;
	int size;
	int front;
	int rear;
};

void init_queue(struct queue *q, int size)
{
	q->size = size;
	q->data = (int *)calloc(size, sizeof(int));
	q->front = q->rear = 0;
}

int empty_queue(struct queue *q)
{
	return q->front == q->rear;
}

void add_queue(struct queue *q, int x)
{
	if (((q->front + 1) % q->size) == q->rear) {
		printf("full\n");
		return;
	}
	q->data[q->front] = x;
	q->front = (q->front + 1) % q->size;
}

int del_queue(struct queue *q)
{
	int ret = q->data[q->rear];
	q->data[q->rear] = 0;
	if (empty_queue(q)) {
		printf("emptry\n");
		return -1;
	}
	q->rear = (q->rear + 1) % q->size;
	return ret;
}

void print_queue(struct queue *q)
{
	for (int i = 0; i < q->size; i++) {
		printf("%d ", q->data[i]);
	}
	printf("\n");
}
	
struct node
{
	int children[100];
	int children_size;
	int visited;
};

struct graph
{
	struct node *nodes[100];
	int node_size;
};


int bfs_list(void)
{
	struct queue qqq;
	init_queue(&qqq, 20);

	struct node node0 = {{1, 4, 5}, 3, 0};
	struct node node1 = {{4, 3}, 2, 0};
	struct node node2 = {{1}, 1, 0};
	struct node node3 = {{2, 4}, 2, 0};
	struct node node4 = {{}, 0, 0};
	struct node node5 = {{6}, 1, 0};
	struct node node6 = {{}, 0, 0};

	struct graph bfs = {{&node0, &node1, &node2, &node3, &node4, &node5, &node6}, 7};

	bfs.nodes[0]->visited = 1;
	add_queue(&qqq, 0);

	while (!empty_queue(&qqq)) {
		int index = del_queue(&qqq);

		for (int i = 0; i < bfs.nodes[index]->children_size; i++) {
			int next = bfs.nodes[index]->children[i];
			if (bfs.nodes[next]->visited == 0) {
				bfs.nodes[next]->visited = 1;
				printf("VISIT=%d\n", next);
				add_queue(&qqq, next);
			}
		}
	}

	return 0;
}

int matrix[7][7] = {
	//    0 1 2 3 4 5 6
	/*0*/{0,1,0,0,1,1,0},
	/*1*/{0,0,0,1,1,0,0},
	/*2*/{0,1,0,0,0,0,0},
	/*3*/{0,0,1,0,1,0,0},
	/*4*/{0,0,0,0,0,0,0},
	/*5*/{0,0,0,0,0,0,1},
	/*6*/{0,0,0,0,0,0,0}};

int visited[7];

void dfs(int current)
{
	printf("dfs visit=%d\n", current);
	visited[current] = 1;

	for (int i = 0; i < 7; i++) {
		if (matrix[current][i] == 1 && visited[i] == 0) {
			dfs(i);
		}
	}
}

void bfs_matrix(int root)
{
	struct queue qqq;
	init_queue(&qqq, 20);

	visited[root] = 1;
	add_queue(&qqq, root);

	while (!empty_queue(&qqq)) {
		int next = del_queue(&qqq);

		for (int i = 0; i < 7; i++) {
			if (matrix[next][i] == 1 && visited[i] == 0) {
				visited[i] = 1;
				printf("bfs visit=%d\n", i);
				add_queue(&qqq, i);
			}
		}
	}
}

int main(void)
{
	//dfs(0);
	bfs_list();
	bfs_matrix(0);
	
	return 0;
}
