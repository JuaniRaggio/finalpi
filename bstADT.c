#include <stdlib.h>
#include "errorManagement.h"
#include "bstADT.h"

struct node {
    void * value;
    size_t nodeHeight;
    struct node * left;
    struct node * right;
};

struct bstCDT {
    struct node * root;
    struct node * inorderIterator;
    struct node * preorderIterator;
    struct node * postorderIterator;
    size_t sizeValue;
    size_t nodeCounter;
    size_t treeHeight;
    cmp fx;
};

bstADT newBst(size_t size, cmp fx) {
    bstADT newTree = calloc(1, sizeof(struct bstCDT));
    assert(newTree == NULL);
    newTree->sizeValue = size;
    newTree->fx = fx;
    return newTree;
}

unsigned int size(const bstADT bst) {
    return bst->nodeCounter;
}

unsigned int height(const bstADT bst) {
    return bst->treeHeight;
}

unsigned int nodeHeight(struct node *N) {
    if (N == NULL) {
        return 0;
    }
    return N->nodeHeight;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

typedef struct node * node;

struct node * rightRotate(struct node *y) {
    struct node * x = y->left;
    struct node * T2 = x->right;
    x->right = y;
    y->left = T2;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    return x;
}

struct node * leftRotate(struct node *x) {
    struct node * y = x->right;
    struct node * T2 = y->left;
    y->left = x;
    x->right = T2;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}


int insert(bstADT bst, void * elem) {
}

void freeBstRec(struct node * root) {
    if (root == NULL) return;
    freeBstRec(root->left);
    freeBstRec(root->right);
    free(root);
}

void freeBst(bstADT bst) {
    freeBstRec(bst->root);
    free(bst);
}



