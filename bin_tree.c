#include <stdio.h>
#include <stdlib.h>

struct tnode {
	int val;
	struct tnode *left, *right;
};

void _insert(struct tnode *root, int val)
{
	if (root->val > val) {
		if (root->left)
			return _insert(root->left, val);
		else {
			root->left = calloc(1, sizeof(struct tnode));
			root->left->val = val;
			return;
		}
	} else if (root->val < val) {
		if (root->right)
			return _insert(root->right, val);
		else {
			root->right = calloc(1, sizeof(struct tnode));
			root->right->val = val;
			return;
		}
	} else
		return;
}

void bintree_insert(struct tnode **root, int val)
{
	if (!(*root)) {
		(*root) = calloc(1, sizeof(struct tnode));
		(*root)->val = val;
		return;
	}

	_insert((*root), val);
}


struct tnode *build_test_tree(int *data, int num)
{
	struct tnode *root = NULL;
	int i;
	for (i = 0; i < num; i++)
		bintree_insert(&root, data[i]);
	return root;
}

void print_inorder(struct tnode *root)
{
	if (!root) return;
	print_inorder(root->left);
	printf("%d\n", root->val);
	print_inorder(root->right);	
}
void print_preorder(struct tnode *root)
{
	if (!root) return;
	printf("%d\n", root->val);
	print_preorder(root->left);
	print_preorder(root->right);
}
void print_postorder(struct tnode *root)
{
	if (!root) return;
	print_postorder(root->left);
	print_postorder(root->right);
	printf("%d\n", root->val);
}

int main(void)
{
	int data[] = {5,3,4,2,7,6};
	struct tnode *root = build_test_tree(data, sizeof(data)/sizeof(int));

	printf("root=%d\n", root->val);

	printf("inorder\n");
	print_inorder(root);
	printf("preorder\n");
	print_preorder(root);
	printf("postorder\n");
	print_postorder(root);
}
