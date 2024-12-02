#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "errorManagement.h"
#include "agencysADT.h"
#include "bstADT.h"

#define MONTHS 12
#define PLATE_LEN 10

typedef struct infraction {
    char plate[PLATE_LEN + 1];
    char * issueDate;
    size_t infractionID;
    size_t amount;
} TInfraction;

typedef struct year {
    size_t yearN;
    size_t collected[MONTHS];
    // Ver si es arbol -> left + right
    // Si es list -> next
    // Si es HT -> nada
} TYear;

typedef struct agency {
    char * agencyName;
    size_t * infractionAmount;
    size_t maxID;
    size_t maxAmount;
    size_t minAmount;
    // Ver si arbol de años, lista de años o hashTable de años
} TAgency;

typedef struct node {
    TAgency * agencyData;
    size_t nodeHeight;
    struct node * left;
    struct node * right;
} TNode;

struct bstCDT {
    TNode * root;
    size_t agencyCounter;
    size_t treeHeight;
    cmp fx;
};


TNode * insertRec(TNode * root, cmp fx, elemType element, int * added, size_t * height) {
    int comparison;
    if (root == NULL) {
        TNode * newNode = calloc(1, sizeof(TNode));
        newNode->agencyData = element;
        ++*height;
        *added = 1;
        return newNode;
    } else if ((comparison = fx(root->agencyData, element)) == 0) {
        *added = 0;
        return root;
    }
    ++*height;
    if (comparison < 0) {
        root->right = insertRec(root->right, fx, element, added, height);
    } else {
        root->left = insertRec(root->left, fx, element, added, height);
    }
    return root;
}

// Agrega un elemento respetando el orden
// Retorna 1 si lo pudo agregar (no estaba), cero si no (ya estaba)
int insert(bstADT bst, elemType elem) {
    int added = 0;
    size_t height = 0;
    bst->root = insertRec(bst->root, bst->fx, elem, &added, &height);
    bst->agencyCounter += added;
    if (height > bst->treeHeight) bst->treeHeight = height;
    return added;
}

TNode * insertAgencyRec(TNode * root, char * agencyName, TInfraction * data) {
}

// If added returns true
// else false
bool insertInfraction(bstADT agencyBST, char * agencyName, char * plate, char * issueDate, size_t infractionID, size_t amount) {
    bool added = false;
    TInfraction * data = malloc(sizeof(TInfraction));
    assert(data == NULL, ENOMEM, false);
    data->amount = amount;
    data->infractionID = infractionID;
    data->issueDate = malloc(strlen(issueDate) + 1);
    strcpy(data->issueDate, issueDate);
    strncpy(data->plate, plate, PLATE_LEN + 1);
    agencyBST->root = insertAgencyRec(agencyBST->root, agencyName, data);
    agencyBST->treeHeight += added;
    agencyBST->agencyCounter += added;
    return added;
}

void inorderRec(elemType * orderedVector, size_t * idx, TNode * root) {
    if (root == NULL) return;
    // 1. copiar el de la izquierda
    inorderRec(orderedVector, idx, root->left);
    // 2. copiar el actual
    orderedVector[(*idx)++] = root->agencyData;
    // 3. copiar el de la derecha
    inorderRec(orderedVector, idx, root->right);
}

// Retorna un vector con los elementos almacenados de acuerdo a un recorrido inorder
// La cantidad de elementos del vector esta dada por la funcion size
elemType * inorder(const bstADT bst) {
    if (bst->agencyCounter == 0) return NULL;
    elemType * orderedVector = malloc(sizeof(elemType) * bst->agencyCounter);
    size_t idx = 0;
    inorderRec(orderedVector, &idx, bst->root);
    return orderedVector;
}

bstADT newBST(cmp fx) {
    bstADT newTree = calloc(1, sizeof(struct bstCDT));
    assert(newTree == NULL, ENOMEM, NULL);
    newTree->fx = fx;
    return newTree;
}

unsigned int sizeBST(const bstADT bst) {
    return bst->agencyCounter;
}

unsigned int heightBST(const bstADT bst) {
    return bst->treeHeight;
}

unsigned int nodeHeight(TNode * node) {
    if (node == NULL) {
        return 0;
    }
    return node->nodeHeight;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

TNode * rightRotate(TNode *y) {
    TNode * x = y->left;
    TNode * T2 = x->right;
    x->right = y;
    y->left = T2;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    return x;
}

TNode * leftRotate(TNode *x) {
    TNode * y = x->right;
    TNode * T2 = y->left;
    y->left = x;
    x->right = T2;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}


void freeBstRec(TNode * root) {
    if (root == NULL) return;
    freeBstRec(root->left);
    freeBstRec(root->right);
    free(root);
}

void freeBst(bstADT bst) {
    freeBstRec(bst->root);
    free(bst);
}



