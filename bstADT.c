#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

// If added returns true
// else false
bool insert(bstADT bst, const void * elem) {
    bool added = false;
    for (struct node * toAdd = bst->root, * prev = bst->root, * pivot = bst->root; !added;) {
        if (prev == NULL) {
            struct node * newRoot = calloc(1, sizeof(struct node));
            assert(newRoot == NULL, ENOMEM, false);
            // Ver como leemos las cosas del csv
            memcpy(newRoot->value, elem, bst->sizeValue);
        }
    }
}

bstADT newBst(size_t size, cmp fx) {
    bstADT newTree = calloc(1, sizeof(struct bstCDT));
    assert(newTree == NULL, ENOMEM, NULL);
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



