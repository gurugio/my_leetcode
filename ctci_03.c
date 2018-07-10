#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct stack_node {
	int val;
	struct stack_node *min_next; // ex3.2
	struct stack_node *next;
};

struct stack {
	struct stack_node *top;
	struct stack_node *min_top; // ex3.2
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
	if (!stack->min_top || stack->min_top->val > val) {
		n->min_next = stack->min_top;
		stack->min_top = n;
	}
}

int stack_min(struct stack *stack)
{
	return stack->min_top ? stack->min_top->val : -1;
}
	      
int stack_peek(struct stack *stack)
{
	return stack->top->val;
}

int stack_empty(struct stack *stack)
{
	return !stack->top;
}

int stack_pop(struct stack *stack)
{
	int ret;
	struct stack_node *n = stack->top;

	if (stack_empty(stack)) {
		printf("stack-empty\n");
		return 0;
	}
	ret = stack->top->val;
	stack->top = n->next;
	if (n == stack->min_top) {
		stack->min_top = n->min_next;
	}
	free(n);
	return ret;
}

int queue_empty(struct queue *queue)
{
	if ((queue->tail && !queue->head) || (!queue->tail && queue->head))
		printf("queue error\n");
	return !queue->head;
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
	int ret;
	struct queue_node *n = queue->head;

	if (queue_empty(queue)) {
		printf("queue-empty\n");
		return 0;
	}
	ret = queue->head->val;
	queue->head = n->next;
	free(n);
	if (queue->head == NULL)
		queue->tail = NULL;
	return ret;
}

void basic_test(void)
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
}


void test_ex_3_2(void)
{
	int i;
	srand(time(NULL));
	struct stack *s = calloc(1, sizeof(*s));

	for (i = 0; i < 10; i++) {
		int t = rand() % 100;
		printf("%d ", t);
		stack_push(s, t);

		printf("min=%d\n", stack_min(s));
	}
	printf("\n");

	printf("pop:  ");
	for (i = 0; i < 10; i++) {
		printf("%d ", stack_pop(s));
		printf("min=%d\n", stack_min(s));
	}
	printf("\n");
}

#define ADD 11
#define REMOVE 22

struct myqueue {
	struct stack *front;
	struct stack *back;
	int last_cmd;
};

struct myqueue *myqueue_alloc(void)
{
	struct myqueue *q = calloc(1, sizeof(*q));
	q->front = calloc(1, sizeof(struct stack));
	q->back = calloc(1, sizeof(struct stack));
	q->last_cmd = 0;
	return q;
}

void myqueue_reverse(struct myqueue *q)
{
	int val;
	struct stack *t;
	while (!stack_empty(q->front)) {
		val = stack_pop(q->front);
		stack_push(q->back, val);
	}

	t = q->front;
	q->front = q->back;
	q->back = t;
}

void myqueue_add(struct myqueue *q, int val)
{
	if (q->last_cmd == 0 || q->last_cmd == ADD) {
		stack_push(q->front, val);
	} else {
		myqueue_reverse(q);
		stack_push(q->front, val);
	}
	q->last_cmd = ADD;
}

int myqueue_remove(struct myqueue *q)
{
	int ret;
	if (q->last_cmd == 0 || q->last_cmd == REMOVE) {
		ret = stack_pop(q->front);
	} else {
		myqueue_reverse(q);
		ret = stack_pop(q->front);
	}
	q->last_cmd = REMOVE;
	return ret;
}

void test_ex_3_4(void)
{
	struct myqueue *q = myqueue_alloc();
	stack_push(q->front, 1);
	stack_push(q->front, 2);
	stack_push(q->front, 3);
	myqueue_reverse(q);
	printf("%d\n", stack_pop(q->front));
	printf("%d\n", stack_pop(q->front));
	printf("%d\n", stack_pop(q->front));

	myqueue_add(q, 1);
	myqueue_add(q, 2);
	myqueue_add(q, 3);
	printf("%d\n", myqueue_remove(q));
	myqueue_add(q, 4);
	myqueue_add(q, 5);
	printf("%d\n", myqueue_remove(q));
	myqueue_add(q, 6);
	printf("%d\n", myqueue_remove(q));
	myqueue_add(q, 7);
	myqueue_add(q, 8);
	myqueue_add(q, 9);
	printf("%d\n", myqueue_remove(q));
	printf("%d\n", myqueue_remove(q));
	printf("%d\n", myqueue_remove(q));
	printf("%d\n", myqueue_remove(q));
	printf("%d\n", myqueue_remove(q));
	printf("%d\n", myqueue_remove(q));
}

int main(void)
{
	//test_ex_3_2();
	test_ex_3_4();
	return 0;
}
