#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validIDADT.h"
#include "errorManagement.h"
#include "bstADT.h"

// Ver como manejamos los maxdesclen
#define MAX_DESCRIPTION_LEN 50

#define MONTHS 12
#define PLATE_LEN 10

typedef struct ticket {
    char plate[PLATE_LEN];
    char * issueDate;
    size_t infractionID;
    size_t amount;
} TTicket;

typedef struct LInfraction {
	unsigned char ID;
	size_t amount;
	struct LInfraction * next;
} LInfraction;

typedef struct LYear {
    size_t yearN;
    size_t collected[MONTHS];
    struct year * next;
} LYear;

typedef struct agency {
    char * agencyName;
    LInfraction * infractionList;
    size_t maxID;
    LYear * firstYear;
} TAgency;

typedef struct node {
    TAgency * agencyData;
    size_t nodeHeight;
    struct node * left;
    struct node * right;
} TNode;

struct bstCDT {
    TNode * root;
    TNode * iterator;
    size_t agencyCounter;
    size_t treeHeight;
};

TNode * insertAgencyRec(TNode * root, char * agencyName, LInfraction * data) {
    return NULL;
}

// If added returns true
// else false
bool insertInfraction(bstADT agencyBST, validIDADT validIDs, char * agencyName, char * plate, char * issueDate, size_t infractionID, size_t amount) {
    bool added = false;
    // Dependiendo en como implementemos Q2 y Q3 podriamos evitar alocar memoria
    // Q1 ya funcionaria con el vector que creamos "infractionAmount" en "TAgency"
    LInfraction * data = malloc(sizeof(LInfraction));
    assert(data == NULL, ENOMEM, false);
    data->ID = infractionID;
    data->amount = amount;

    agencyBST->root = insertAgencyRec(agencyBST->root, agencyName, data);
    agencyBST->treeHeight += added;
    agencyBST->agencyCounter += added;
    return added;
}

/* void inorderRec(elemType * orderedVector, size_t * idx, TNode * root) { */
/*     if (root == NULL) return; */
/*     // 1. copiar el de la izquierda */
/*     inorderRec(orderedVector, idx, root->left); */
/*     // 2. copiar el actual */
/*     orderedVector[(*idx)++] = root->agencyData; */
/*     // 3. copiar el de la derecha */
/*     inorderRec(orderedVector, idx, root->right); */
/* } */

// HAY QUE CAMBIARLO PARA QUE RETORNE ELEMENTO POR ELEMENTO, PODRIAMOS USAR ITERADOR SI ES NECESARIO

// Retorna un vector con los elementos almacenados de acuerdo a un recorrido inorder
// La cantidad de elementos del vector esta dada por la funcion size
/* elemType * inorder(const bstADT bst) { */
/*     if (bst->agencyCounter == 0) return NULL; */
/*     elemType * orderedVector = malloc(sizeof() * bst->agencyCounter); */
/*     size_t idx = 0; */
/*     inorderRec(orderedVector, &idx, bst->root); */
/*     return orderedVector; */
/* } */

bstADT newBST(void) {
    bstADT newTree = calloc(1, sizeof(struct bstCDT));
    assert(newTree == NULL, ENOMEM, NULL);
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



