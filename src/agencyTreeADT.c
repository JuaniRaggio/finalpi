#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "../include/formats.h"
#include "../include/validIDADT.h"
#include "../include/errorManagement.h"
#include "../include/agencyTreeADT.h"
#include "../include/lib.h"

typedef struct LTicket {
	unsigned char id;
	size_t units;
	struct LTicket * next;
} LTicket;

typedef struct LYear {
    size_t yearN;
    size_t collected[MONTHS];
    struct year * next;
} LYear;

typedef struct agency {
    char agencyName[AGENCY_LEN];
    LTicket * ticketList;
    LYear * firstYear;
} TAgency;

typedef struct node {
    TAgency * agencyData;
    size_t nodeHeight;
    struct node * left;
    struct node * right;
} TNode;

struct agencyTreeCDT {
    validIDADT validIDs;
    TNode * root;
    TNode * iterator;
    size_t agencyCounter;
    size_t treeHeight;
};

static LTicket * addTicket(validIDADT validIDs, LTicket * firstTicket, unsigned char id);
static LYear * addYear(LYear * firstYear, size_t year, size_t amount, size_t month);

TNode * insertAgencyRec(TNode * root, char * agencyName, LTicket * data) {
    return NULL;
}

static void addHeight( TNode * vec, size_t dim ) {
    while ( dim > 0 ) {
        vec->nodeHeight++;
        dim--;
    }
}

static int balanceFactor ( TNode * root ) {
    return root->left->nodeHeight - root->right->nodeHeight;
} 

TNode * insertAgencyRec(TNode * root, char * agencyName, LInfraction * data, size_t * dim) {
    TNode * vec[*dim];
    TNode * toReturn;
    size_t dimAux = 0, still = 1;
    while ( root != NULL && still ) {
        if ( strcmp(root->agencyData->agencyName, agencyName) < 0 ) { 
            vec[dimAux++] = root;
            root = root->right;
        } else if ( strcmp(root->agencyData->agencyName, agencyName) > 0 ) {
            vec[dimAux++] = root;
            root = root->left;
        } else {
            *toReturn = *root;
            toReturn->agencyData->infractionList->amount = data->amount;
            toReturn->agencyData->infractionList->id = data->id;
            // toReturn->agencyData->infractionList->next a donde apuntaria el next?
            still = 0;
        }
    }

    if ( still ) { // sali porque root es NULL entonces debo crear el nodo y recorro el vec y le sumo height
        
        addHeight(vec,dimAux);
    }

    if ( abs(balanceFactor(root)) >= 2 ) {
        // balanceo el arbol
    } 
    return toReturn;
}

// If added returns true
// else false
bool insertInfraction(agencyTreeADT agencyBST, char * agencyName, char * plate, char * issueDate, size_t id, size_t amount) {
    bool added = false;
    // Dependiendo en como implementemos Q2 y Q3 podriamos evitar alocar memoria
    // Q1 ya funcionaria con el vector que creamos "infractionAmount" en "TAgency"
    LTicket * data = malloc(sizeof(LTicket));
    errno = NOERRORSFOUND;
    assert(data == NULL, ENOMEM, false);
    data->id = id;
    data->amount = amount;

    agencyBST->root = insertAgencyRec(agencyBST->root, agencyName, data); // falta ver que dim le pasa
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
/* elemType * inorder(const agencyTreeADT agencys) { */
/*     if (agencys->agencyCounter == 0) return NULL; */
/*     elemType * orderedVector = malloc(sizeof() * agencys->agencyCounter); */
/*     size_t idx = 0; */
/*     inorderRec(orderedVector, &idx, agencys->root); */
/*     return orderedVector; */
/* } */

agencyTreeADT newAgencys(void) {
    agencyTreeADT newTree = calloc(1, sizeof(struct agencyTreeCDT));
    errno = NOERRORSFOUND;
    assert(newTree == NULL, ENOMEM, NULL);
    return newTree;
}

unsigned int sizeBST(const agencyTreeADT agencys) {
    return agencys->agencyCounter;
}

unsigned int heightBST(const agencyTreeADT agencys) {
    return agencys->treeHeight;
}

static unsigned int nodeHeight(TNode * node) {
    if (node == NULL) {
        return 0;
    }
    return node->nodeHeight;
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static TNode * rightRotate(TNode *y) {
    TNode * x = y->left;
    TNode * T2 = x->right;
    x->right = y;
    y->left = T2;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    return x;
}

static TNode * leftRotate(TNode *x) {
    TNode * y = x->right;
    TNode * T2 = y->left;
    y->left = x;
    x->right = T2;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}


static void freeBstRec(TNode * root) {
    if (root == NULL) return;
    freeBstRec(root->left);
    freeBstRec(root->right);
    free(root);
}

void freeBst(agencyTreeADT agencys) {
    freeBstRec(agencys->root);
    free(agencys);
}

