#include <stdio.h>

#ifndef __BSTADT_H__
#define __BSTADT_H__

typedef struct bstCDT * bstADT;

typedef struct agencysCDT elemType;

bstADT newBST(void);

// Cambiar
bool insertBST(bstADT tree, char * agencyName, char * infractionID, char plate[], char * issueDate, size_t amount);

#endif


