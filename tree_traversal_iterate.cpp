#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
using namespace std;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? (-(a)) : (a))

struct node {
    struct node* left;
    struct node* right;
    int val;
    bool visited;
};

int main()
{
    struct node node1 {
        NULL, NULL, 1, false
    };
    struct node node2 {
        NULL, NULL, 2, false
    };
    struct node node3 {
        NULL, NULL, 3, false
    };
    struct node node4 {
        NULL, NULL, 4, false
    };
    struct node node5 {
        NULL, NULL, 5, false
    };
    struct node node6 {
        NULL, NULL, 6, false
    };
    struct node node7 {
        NULL, NULL, 7, false
    };
    struct node node8 {
        NULL, NULL, 8, false
    };

    node1.left = &node2;
    node1.right = &node3;

    node2.left = &node4;
    node2.right = &node5;

    node3.left = &node6;
    node3.right = &node7;

    node6.left = &node8;

    struct node* root = &node1;
    vector<struct node*> stack;
    // preorder
    stack.push_back(root);
    while (stack.empty() == false) {
        struct node* cur = stack.back();
        stack.pop_back();

        printf("%d\n", cur->val);
        if (cur->right != NULL) {
            stack.push_back(cur->right);
        }
        if (cur->left != NULL) {
            stack.push_back(cur->left);
        }
    }
    printf("-----------------------\n");

    // inorder
    stack.push_back(root);
    while (stack.empty() == false) {
        struct node* cur = stack.back();

        if (cur->left != NULL && cur->left->visited == false) {
            stack.push_back(cur->left);
        } else {
            stack.pop_back();
            printf("%d\n", cur->val);
            cur->visited = true;
            if (cur->right) {
                stack.push_back(cur->right);
            }
        }
    }

    printf("=========================\n");
    // clear visited
    stack.push_back(root);
    while (stack.empty() == false) {
        struct node* cur = stack.back();
        stack.pop_back();

        cur->visited = false;
        if (cur->right != NULL) {
            stack.push_back(cur->right);
        }
        if (cur->left != NULL) {
            stack.push_back(cur->left);
        }
    }

    // postorder
    stack.push_back(root);
    while (stack.empty() == false) {
        struct node* cur = stack.back();
        if (cur->right && cur->right->visited == false) {
            stack.push_back(cur->right);
        }
        if (cur->left && cur->left->visited == false) {
            stack.push_back(cur->left);
        }
        if ((cur->left == NULL || cur->left->visited == true) && (cur->right == NULL || cur->left->visited == true)) {
            stack.pop_back();
            cur->visited = true;
            printf("%d\n", cur->val);
        }
    }
}