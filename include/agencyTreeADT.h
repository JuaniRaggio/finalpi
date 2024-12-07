#ifndef __AGENCYTREEADT_H__
#define __AGENCYTREEADT_H__

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "lib.h"
#include "formats.h"
#include "errorManagement.h"
#include "validIDADT.h"

typedef struct agencyTreeCDT * agencyTreeADT;

// Sets errno if needed
agencyTreeADT newAgencys(validIDADT);

unsigned int sizeBST(const agencyTreeADT agencys);

// Sets errno if needed
// Adds agency to agencyTreeADT
// @param agencyName: new agency's name
// @param tData: data to insert in agency
bool insertAgency(agencyTreeADT agency, char * agencyName, TTicket * tData);

// 1 - Initialize agency with toBeginAgency
// 2 - Request agencys alphabetically with nextAgency
// 3 - For each request, use toBeginTicket, nextTicket, toBeginYear and nextYear
//     to get the data from that Requested agency
void toBeginAgency(agencyTreeADT agency);
bool hasNextAgency(agencyTreeADT agency);
bool nextAgency(agencyTreeADT agency);

void toBeginTicket(agencyTreeADT agency);
bool hasNextTicket(agencyTreeADT agency);
DTicket nextTicket(agencyTreeADT agency);

void toBeginYear(agencyTreeADT agency);
bool hasNextYear(agencyTreeADT agency);
DYear nextYear(agencyTreeADT agency);

const char * getNameOfIterator(agencyTreeADT agency);
const char * getDescriptionOfIterator(agencyTreeADT agency);

// This iterators are independent from the ones above
// Used to iterate in diffAmount order
void toBeginDiff(agencyTreeADT agency);
bool hasNextDiff(agencyTreeADT agency);
nDDiff nextDiff(agencyTreeADT agency);

// Free resources
void freeAgencys(agencyTreeADT agencys);

#endif

