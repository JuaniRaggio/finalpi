#include <stdio.h>
#include <stdbool.h>

#ifndef __VALIDIDADT_H__
#define __VALIDIDADT_H__

typedef struct validIDCDT * validIDADT;

validIDADT newValidID(void);

bool addID(validIDADT validIDs, unsigned char id, char * description);

bool isValidID(validIDADT validIDs, unsigned char id);

#endif
