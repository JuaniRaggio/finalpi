#include <stdlib.h>
#include "errorManagement.h"
#include "bstADT.h"

struct node {
    void * value;
    size_t sizeValue;
    size_t nodeHeight;
    struct node * left;
    struct node * right;
};

struct bstCDT {
    struct node * root;
    struct node * inorderIterator;
    struct node * preorderIterator;
    struct node * postorderIterator;
    size_t nodeCounter;
    size_t treeHeight;
    cmp fx;
};


bstADT newBst(cmp fx) {
    bstADT newTree = calloc(1, sizeof(struct bstCDT));
    assert(newTree == NULL);
    newTree->fx = fx;
    return newTree;
}

