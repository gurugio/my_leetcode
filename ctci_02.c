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

int list_nth_back(struct list_node *n, int k)
{
	int t;
	if (n->next == NULL)
		return 1;
	t = list_nth_back(n->next, k) + 1;
	if (t == k)
		printf("n-th=%d\n", n->val);
	return t;
}

struct list_node *list_add_val(struct list_node *n1,
							   struct list_node *n2)
{
	int carry = 0;
	struct list_node *cur = NULL, *ret;
	struct list_node *na, *nb;
	
	for (na = n1, nb = n2; na && nb; na = na->next, nb = nb->next) {
		if (cur) {
			cur->next = calloc(1, sizeof(*cur));
			cur = cur->next;
		} else {
			cur = calloc(1, sizeof(*cur));
			ret = cur;
		}
		cur->val = (na->val + nb->val + carry) % 10;
		carry = (na->val + nb->val + carry) / 10;
	}
	for (; na; na = na->next) {
		cur->next = calloc(1, sizeof(*cur));
		cur = cur->next;
		cur->val = (na->val + carry) % 10;
		carry = (na->val + carry) / 10;
	}
	for (; nb; nb = nb->next) {
		cur->next = calloc(1, sizeof(*cur));
		cur = cur->next;
		cur->val = (nb->val + carry) % 10;
		carry = (nb->val + carry) / 10;
	}
	return ret;
}

void list_print(struct list_node *n)
{
	int i;
	for (; n; n=n->next)
		printf("%2d ", n->val);
	printf("\n");
}

int main(void)
{
	int i;
	srand(time(NULL));

	ex_2_1();

	struct list_node *head = calloc(1, sizeof(*head));
	head->val = rand() % 10;
	for (i = 0; i < 5; i++) {
		list_insert(head, rand() % 10);
	}
	list_nth_back(head, 3); // ex2.2

	struct list_node *head2 = calloc(1, sizeof(*head2));
	head2->val = rand() % 10;
	for (i = 0; i < 10; i++) {
		list_insert(head2, rand() % 10);
	}
	list_print(head);
	list_print(head2);
	list_print(list_add_val(head, head2)); // ex2.5

	return 0;
}
