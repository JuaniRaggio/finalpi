#include <stdio.h>

#ifndef __BSTADT_H__
#define __BSTADT_H__

typedef struct bstCDT * bstADT;

typedef int (*cmp)(const char *, const char *);

bstADT newBST(size_t size, cmp fx);

bool insertBST(bstADT tree, const void * elem);

#endif


