#include "../include/formats.h"
#include "../include/validIDADT.h"
#include <stdio.h>

#ifndef __AGENCYTREEADT_H__
#define __AGENCYTREEADT_H__

typedef struct agencyTreeCDT * agencyTreeADT;

/* typedef struct agencysCDT elemType; */

agencyTreeADT newAgencys(validIDADT);

unsigned int heightBST(const agencyTreeADT agencys);

unsigned int sizeBST(const agencyTreeADT agencys);

bool insertAgency(agencyTreeADT agency, char * agencyName, TTicket * tData);

void freeBst(agencyTreeADT agencys);

#endif

