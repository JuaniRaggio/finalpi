#include "../include/validIDADT.h"
#include <stdio.h>

#ifndef __AGENCYTREEADT_H__
#define __AGENCYTREEADT_H__

typedef struct agencyTreeCDT * agencyTreeADT;

typedef struct agencysCDT elemType;

agencyTreeADT newAgencys(void);

bool insertInfraction(agencyTreeADT agencyBST, validIDADT validIDs, char * agencyName, char * plate, char * issueDate, size_t infractionID, size_t amount);

#endif

