#include "../include/validIDADT.h"
#include <stdio.h>

#ifndef __DIFFTREEADT_H__
#define __DIFFTREEADT_H__

typedef struct diffTreeCDT * diffTreeADT;

typedef struct diff {
    unsigned char id;
    size_t diffAmount;
    size_t minAmount;
    size_t maxAmount;
} DDiff;

diffTreeADT newDiff(validIDADT validIDs);

void toBeginDiff(diffTreeADT diffTree);

bool hasNextDiff(diffTreeADT diffTree);

DDiff nextDiff(diffTreeADT diffTree);

bool insertDiff(diffTreeADT diffTree,TTicket * ticket, char * agencyName);

void freeDiff(diffTreeADT diffTree);

#endif


