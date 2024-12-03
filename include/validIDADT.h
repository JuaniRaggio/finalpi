#include <stdio.h>
#include <stdbool.h>

#ifndef __VALIDIDADT_H__
#define __VALIDIDADT_H__

typedef struct validIDCDT * validIDADT;

// Creates a new ADT to add and ask for valid IDs
validIDADT newValidID(void);

// Adds a valid ID, if the ID is added successfully returns ture else returns false
bool addID(validIDADT validIDs, unsigned char id, char * description);

// Validates ID
bool isValidID(validIDADT validIDs, unsigned char id);

#endif
