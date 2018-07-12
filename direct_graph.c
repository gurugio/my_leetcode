#include <stdio.h>
#include <stdlib.h>

#define QSIZE 6
struct queue {
	struct vertex *buffer[QSIZE];
	int head, tail;
};

struct queue *queue_alloc(void)
{
	struct queue *q = calloc(1, sizeof(*q));
	q->head = q->tail = 0;
	return q;
}

int queue_add(struct queue *q, struct vertex *v)
{
	if ((q->tail + 1) % QSIZE == q->head)
		return 0;
	q->buffer[q->tail] = v;
	q->tail = (q->tail + 1) % QSIZE;
	return 1;
}

struct vertex *queue_remove(struct queue *q)
{
	struct vertex *v;

	if (q->head == q->tail)
		return NULL;
	v = q->buffer[q->head];
	q->head = (q->head + 1) % QSIZE;
	return v;
}

int queue_empty(struct queue *q)
{
	return q->head == q->tail;
}

void queue_print(struct queue *q)
{
	int i;
	printf("h:%d t:%d\n", q->head, q->tail);
	for (i = 0; i < QSIZE; i++)
		printf("%ld ", (unsigned long)q->buffer[i]);
	printf("\n");
}

void queue_test(void)
{
	unsigned long i;
	struct queue *q = queue_alloc();
	for (i = 1; i <= QSIZE + 1; i++) 
		printf("%d\n", queue_add(q, (struct vertex *)i));
	queue_print(q);
	for (i = 1; i <= QSIZE + 1; i++) 
		printf("%ld\n", (unsigned long)queue_remove(q));
	queue_print(q);	
	for (i = 11; i <= 13; i++) 
		printf("%d\n", queue_add(q, (struct vertex *)i));
	queue_print(q);
	for (i = 0; i <1; i++) 
		printf("%ld\n", (unsigned long)queue_remove(q));
	queue_print(q);	
	for (i = 111; i <= 113; i++) 
		printf("%d\n", queue_add(q, (struct vertex *)i));
	queue_print(q);
}

struct arc;
struct vertex;

struct arc {
	struct vertex *vertex;
	/* prev is not necessary but I added it to practice double-linked list */
	struct arc *prev, *next;
	int weight;
};

struct vertex {
	int id;
#define VERTEX_VISIT 0x1
	unsigned int flag;
	struct arc *arc;
};

struct vertex *create_graph(int num)
{
	int i;
	struct vertex *gra = calloc(num, sizeof(*gra));
	for (i = 0; i < num; i++) {
		gra[i].id = i;
	}
	return gra;
}

void insert_vertex(struct vertex *gra, int from, int to, int weight)
{
	struct arc *arc = calloc(1, sizeof(*arc));
	arc->prev = arc;
	arc->next = arc;
	arc->weight = weight;
	arc->vertex = &gra[to];

	if (!gra[from].arc) {
		gra[from].arc = arc;
	} else {
		arc->prev = gra[from].arc->prev;
		arc->next = gra[from].arc;
		gra[from].arc->prev->next = arc;
		gra[from].arc->prev = arc;
	}
}

void print_arc(struct vertex *gra, int id)
{
	struct arc *arc;

	printf("from [%d]: ", id);
	if (gra[id].arc) {
		arc = gra[id].arc;
		do {
			printf("%d ", arc->vertex->id);
			arc = arc->next;
		} while (arc != gra[id].arc);
	}
	printf("\n");
}

void depth_traversal(struct vertex *gra)
{
	struct arc *arc;

	while (1) {
		printf("VISIT:%d\n", gra->id);
		gra->flag |= VERTEX_VISIT;

		arc = gra->arc;
		do {
			if (arc->vertex->flag & VERTEX_VISIT) {
				arc = arc->next;
				continue;
			}
			break;
		} while (arc != gra->arc);

		if (arc->vertex->flag & VERTEX_VISIT)
			break;
		else
			gra = arc->vertex;
	}
}

void graph_depth_traversal(void)
{
	struct vertex *graph = create_graph(6);
	insert_vertex(graph, 0, 1, 1);
	print_arc(graph, 0);
	insert_vertex(graph, 1, 2, 1);
	insert_vertex(graph, 1, 4, 1);
	print_arc(graph, 1);
	insert_vertex(graph, 2, 1, 1);
	insert_vertex(graph, 2, 3, 1);
	insert_vertex(graph, 2, 4, 1);
	print_arc(graph, 2);
	insert_vertex(graph, 3, 2, 1);
	insert_vertex(graph, 3, 4, 1);
	print_arc(graph, 3);
	insert_vertex(graph, 4, 1, 1);
	insert_vertex(graph, 4, 2, 1);
	insert_vertex(graph, 4, 3, 1);
	insert_vertex(graph, 4, 5, 1);
	print_arc(graph, 4);
	insert_vertex(graph, 5, 4, 1);
	print_arc(graph, 5);

	depth_traversal(graph);
}

void breadth_traversal(struct vertex *graph)
{
	struct queue *q = queue_alloc();
	struct arc *arc;
	
	queue_add(q, graph);
	graph->flag = VERTEX_VISIT;
	printf("VISIT:%d\n", graph->id);

	while (!queue_empty(q)) {
		graph = queue_remove(q);
		arc = graph->arc;
		do {
			if (arc->vertex->flag != VERTEX_VISIT) {
				arc->vertex->flag = VERTEX_VISIT;
				queue_add(q, arc->vertex);
				printf("VISIT:%d\n", arc->vertex->id);
			}
			arc = arc->next;
		} while (arc != graph->arc);
	}
}

void graph_breadth_traversal(void)
{
	struct vertex *graph = create_graph(6);
	insert_vertex(graph, 0, 1, 1);
	print_arc(graph, 0);
	insert_vertex(graph, 1, 2, 1);
	insert_vertex(graph, 1, 4, 1);
	print_arc(graph, 1);
	insert_vertex(graph, 2, 1, 1);
	insert_vertex(graph, 2, 3, 1);
	insert_vertex(graph, 2, 4, 1);
	print_arc(graph, 2);
	insert_vertex(graph, 3, 2, 1);
	insert_vertex(graph, 3, 4, 1);
	print_arc(graph, 3);
	insert_vertex(graph, 4, 1, 1);
	insert_vertex(graph, 4, 2, 1);
	insert_vertex(graph, 4, 3, 1);
	insert_vertex(graph, 4, 5, 1);
	print_arc(graph, 4);
	insert_vertex(graph, 5, 4, 1);
	print_arc(graph, 5);

	breadth_traversal(graph);
}

int main(void)
{
	//queue_test();
	//graph_depth_traversal();
	graph_breadth_traversal();
	return 0;
}
