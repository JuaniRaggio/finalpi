#include "agencysADT.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef __HASHTABLEADT_H__
#define __HASHTABLEADT_H__

typedef struct hashTableCDT * hashTableADT;

hashTableADT newHashTable(void);

bool insertHT(hashTableADT hst, char * agencyName, char * infractionID, char plate[], char * issueDate, size_t amount);

unsigned long hashFunction(unsigned char *str);

#endif

