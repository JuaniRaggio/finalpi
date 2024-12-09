#ifndef __GENERICAVLTREEADT_H__
#define __GENERICAVLTREEADT_H__

#include "genericStackADT.h"

typedef struct genericAVLTreeCDT * genericAVLTreeADT;
typedef struct genericAVLTreeCDT AVLNode;
typedef int (*cmp)(const void *, const void *);
typedef void (*updateNode)(const void * current, const void * toUpdate_Nullable);

void freeAgencyTreeRec(AVLNode * root);
unsigned char nodeHeight(AVLNode * node);
signed char balanceFactor(AVLNode * root);
AVLNode * rightRotate(AVLNode * y);
AVLNode * leftRotate(AVLNode * x);
AVLNode * insertNode(AVLNode * root,  cmp compare, updateNode update, AVLNode ** addedNode, void * data);
void updateDiff(AVLNode * root, size_t amount);

#endif

