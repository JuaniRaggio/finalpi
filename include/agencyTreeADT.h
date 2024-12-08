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
/// Creates new agencies.
/// @param validInfractions: ADT of valid infractions
agencyTreeADT newAgencys(validIDADT validInfractions);

/// Returns the size of agencyTree.
/// @param agencys: ADT of stored agencies.
unsigned int sizeBST(const agencyTreeADT agencys);

// Sets errno if needed
// Adds agency to agencyTreeADT
// if true -> there's data saved in iterator
// else -> no data left
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


/// Returns name of current agency pointer by the iterator
/// @param agency: ADT of stored agencys 
const char * getNameOfIterator(agencyTreeADT agency);

/// Gets the description associated with a given id
/// @param agency: ADT of stored agencies.
/// @param id: ID_TYPE data type that represents the id.
const char * getDescriptionOfidAtAgency(agencyTreeADT agency, ID_TYPE id);

// This iterators are independent from the ones above
// Used to iterate in diffAmount order
void toBeginDiff(agencyTreeADT agency);
bool hasNextDiff(agencyTreeADT agency);
nDDiff nextDiff(agencyTreeADT agency);

// Free resources
void freeAgencys(agencyTreeADT agencys);

#endif

