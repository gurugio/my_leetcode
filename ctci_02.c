#include <stdio.h>
#include <stdlib.h>

struct btree_node {
	int val;
	struct btree_node *left, *right;
};

struct list_node {
	int val;
	struct list_node *next;
};

int _insert(struct btree_node *root, int val)
{
	if (val < root->val) {
		if (root->left)
			return _insert(root->left, val);
		else {
			root->left = calloc(1, sizeof(*root));
			root->left->val = val;
			return 1;
		}
	} else if (val > root->val) {
		if (root->right)
			return _insert(root->right, val);
		else {
			root->right = calloc(1, sizeof(*root));
			root->right->val = val;
			return 1;
		}
	}
	return 0;
}

int btree_insert(struct btree_node **root, int val)
{
	if (!(*root)) {
		(*root) = calloc(1, sizeof(**root));
		(*root)->val = val;
		return 1;
	}
	return _insert(*root, val);
}

int btree_check(struct btree_node *root, int val)
{
	if (val == root->val)
		return 1;
	else if (val < root->val)
		return btree_check(root->left, val);
	else
		return btree_check(root->right, val);
}

void btree_print(struct btree_node *root)
{
	if (!root)
		return;
	btree_print(root->left);
	printf("%d\n", root->val);
	btree_print(root->right);
}

void list_insert(struct list_node *head, int val)
{
	struct list_node *node = calloc(1, sizeof(*head));
	node->val = val;
	node->next = head->next;
	head->next = node;
}

void ex_2_3(struct list_node *node)
{
	struct list_node *next;
	printf("del: %d %d\n", node->val, node->next->val);
	node->val = node->next->val;
	next = node->next;
	node->next = node->next->next;
	free(next);
}

void ex_2_1(void)
{
	struct list_node *head = calloc(1, sizeof(*head));
	struct btree_node *root = NULL;
	int i;
	srand(time(NULL));

	for (i = 0; i < 10; i++) {
		list_insert(head, rand() % 100);
	}

	for (struct list_node *n = head->next; n; n = n->next)
		printf("before-list: %d\n", n->val);

	for (struct list_node *n = head->next; n; n = n->next) {
		printf("list: %d\n", n->val);
		if (!btree_insert(&root, n->val)) {
			printf("duplicated\n");
			// remove only non-first, non-last
			if (n->next != NULL && n != head->next)
				ex_2_3(n);
		}
	}

	btree_print(root);
	for (struct list_node *n = head->next; n; n = n->next)
		printf("after-list: %d\n", n->val);
}

int main(void)
{
	ex_2_1();

	return 0;
}
