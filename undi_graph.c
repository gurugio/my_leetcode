#include <stdio.h>
#include <stdlib.h>

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

void traversal(struct vertex *gra)
{
	depth_traversal(gra);
}

int main(void)
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

	traversal(graph);
	return 0;
}
