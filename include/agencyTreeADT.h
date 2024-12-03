#include "../include/validIDADT.h"
#include <stdio.h>

#ifndef __AGENCYTREEADT_H__
#define __AGENCYTREEADT_H__

typedef struct agencyTreeCDT * agencyTreeADT;

typedef struct agencysCDT elemType;

agencyTreeADT newAgencys(void);

unsigned int heightBST(const agencyTreeADT agencys);

unsigned int sizeBST(const agencyTreeADT agencys);

bool insertInfraction(agencyTreeADT agencyBST, validIDADT validIDs, char * agencyName, char * plate, char * issueDate, size_t id, size_t amount);

void freeBst(agencyTreeADT agencys);

#endif

