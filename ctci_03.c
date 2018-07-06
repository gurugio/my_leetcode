#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct stack_node {
	int val;
	struct stack_node *next;
};

struct stack {
	struct stack_node *top;
};

struct queue_node {
	int val;
	struct queue_node *next;
};

struct queue {
	struct queue_node *head, *tail;
};

void stack_push(struct stack *stack, int val)
{
	struct stack_node *n = calloc(1, sizeof(*n));
	n->val = val;
	n->next = stack->top;
	stack->top = n;
}

int stack_pop(struct stack *stack)
{
	int ret = stack->top->val;
	struct stack_node *n = stack->top;
	stack->top = n->next;
	free(n);
	return ret;
}

int stack_peek(struct stack *stack)
{
	return stack->top->val;
}

int stack_empty(struct stack *stack)
{
	return !stack->top;
}

void queue_add(struct queue *queue, int val)
{
	struct queue_node *n = calloc(1, sizeof(*n));
	n->val = val;
	if (queue->tail)
		queue->tail->next = n;
	else {
		if (queue->head) printf("queue error\n");
		queue->head = n;
	}
	queue->tail = n;
}

int queue_remove(struct queue *queue)
{
	int ret = queue->head->val;
	struct queue_node *n = queue->head;

	queue->head = n->next;
	free(n);
	if (queue->head == NULL)
		queue->tail = NULL;
	return ret;
}

int queue_empty(struct queue *queue)
{
	if ((queue->tail && !queue->head) || (!queue->tail && queue->head))
		printf("queue error\n");
	return !queue->head;
}

int main(void)
{
	int i;
	srand(time(NULL));
	struct stack *s = calloc(1, sizeof(*s));

	printf("push: ");
	for (i = 0; i < 10; i++) {
		int t = rand() % 10;
		printf("%d ", t);
		stack_push(s, t);
	}
	printf("\n");
	printf("empty=%d\n", stack_empty(s));
	printf("pop:  ");
	for (i = 0; i < 10; i++) {
		printf("%d ", stack_pop(s));
	}
	printf("\n");
	printf("empty=%d\n", stack_empty(s));

	struct queue *q = calloc(1, sizeof(*q));
	printf("q-add: ");
	for (i = 0; i < 10; i++) {
		int t = rand() % 10;
		printf("%d ", t);
		queue_add(q, t);
	}
	printf("\n");
	printf("q-empty=%d\n", queue_empty(q));
	printf("q-rem: ");
	for (i = 0; i < 3; i++)
		printf("%d ", queue_remove(q));
	printf("\n");
	printf("q-empty=%d\n", queue_empty(q));
	printf("q-add: ");
	for (i = 0; i < 10; i++) {
		int t = rand() % 10;
		printf("%d ", t);
		queue_add(q, t);
	}
	printf("\n");
	printf("q-empty=%d\n", queue_empty(q));
	printf("q-rem: ");
	for (i = 0; i < 17; i++)
		printf("%d ", queue_remove(q));
	printf("\n");
	printf("q-empty=%d\n", queue_empty(q));
	
	return 0;
}
