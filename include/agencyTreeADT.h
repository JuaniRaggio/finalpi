#include "../include/formats.h"
#include "../include/validIDADT.h"
#include <stdio.h>

#ifndef __AGENCYTREEADT_H__
#define __AGENCYTREEADT_H__

typedef struct agencyTreeCDT * agencyTreeADT;

typedef struct DYear {
    size_t yearN;
    size_t collected[MONTHS];
} DYear;

typedef struct DTicket {
    unsigned char id;
    size_t units;
} DTicket;

agencyTreeADT newAgencys(validIDADT);

unsigned int sizeBST(const agencyTreeADT agencys);

bool insertAgency(agencyTreeADT agency, char * agencyName, TTicket * tData);

// 1 - Initialize agency with toBeginAgency
// 2 - Request agencys alphabetically with nextAgency
// 3 - For each request, use toBeginTicket, nextTicket, toBeginYear and nextYear
//     to get the data from that Requested agency
void toBeginAgency(agencyTreeADT agency);
bool hasNextAgency(agencyTreeADT agency);
char * nextAgency(agencyTreeADT agency);

void toBeginTicket(agencyTreeADT agency);
bool hasNextTicket(agencyTreeADT agency);
DTicket nextTicket(agencyTreeADT agency);

void toBeginYear(agencyTreeADT agency);
bool hasNextYear(agencyTreeADT agency);
DYear nextYear(agencyTreeADT agency);

void freeAgencys(agencyTreeADT agencys);

#endif

