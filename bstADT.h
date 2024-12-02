#include <stdio.h>

#ifndef __BSTADT_H__
#define __BSTADT_H__

typedef struct bstCDT * bstADT;

typedef struct agencysCDT elemType;

typedef int (*cmp)(const char *, const char *);

bstADT newBST(cmp fx);

// Cambiar
bool insertBST(bstADT tree, char * agencyName, char * infractionID, char plate[], char * issueDate, size_t amount);

#endif


