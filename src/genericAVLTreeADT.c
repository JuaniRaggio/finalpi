#include "../include/genericAVLTreeADT.h"
#include <stdlib.h>
#include <assert.h>

typedef int (*cmp)(const void *, const void *);
typedef void (*updateNode)(const void * current, const void * toUpdate_Nullable);

typedef struct genericAVLTreeCDT {
    void * data;
    cmp compare;
    updateNode update;
    unsigned char nodeHeight;
    struct genericAVLTreeCDT * left;
    struct genericAVLTreeCDT * right;
} AVLNode;

unsigned char nodeHeight(AVLNode * node) {
    if (node == NULL) {
        return 0;
    }
    return node->nodeHeight;
}

signed char balanceFactor(AVLNode * root) {
    return nodeHeight(root->left) - nodeHeight(root->right);
}

AVLNode * rightRotate(AVLNode * y) {
    AVLNode * x = y->left;
    AVLNode * aux = x->right;
    x->right = y;
    y->left = aux;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    return x;
}

AVLNode * leftRotate(AVLNode * x) {
    AVLNode * y = x->right;
    AVLNode * aux = y->left;
    y->left = x;
    x->right = aux;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}


AVLNode * insertNode(AVLNode * root, AVLNode ** addedNode, void * data) {
    if (root == NULL) {
        AVLNode *newNode = malloc(sizeof(AVLNode));
        assert(newNode != NULL);
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        newNode->nodeHeight = 1;
        *addedNode = newNode;
        return newNode;
    }
    int cmp = root->compare(data, root->data);
    if (cmp < 0) {
        root->left = insertNode(root->left, addedNode, data);
    } else if (cmp > 0) {
        root->right = insertNode(root->right, addedNode, data);
    } else {
        root->update(root, data);
        *addedNode = root;
        return root;
    }
    root->nodeHeight = max(nodeHeight(root->left), nodeHeight(root->right)) + 1;
    int balance = balanceFactor(root);
    if (balance > 1 && root->compare(data, root->left->data) < 0) {
        return rightRotate(root);
    } else if (balance < -1 && root->compare(data, root->right->data) > 0) {
        return leftRotate(root);
    } else if (balance > 1 && root->compare(data, root->left->data) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (balance < -1 && root->compare(data, root->right->data) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

