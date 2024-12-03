#include <stdio.h>
#include <stdbool.h>

#ifndef __VALIDIDADT_H__
#define __VALIDIDADT_H__

typedef struct validIDCDT * validIDADT;

// Creates a new ADT to add and ask for valid IDs
validIDADT newValidID(void);

// Adds a valid ID, if the ID is added successfully returns ture else returns false
// @param validIDs: ADT to store and access validIDs
// @param id: Infraction id to add
// @param description: Description from infraction of id:id
bool addID(validIDADT validIDs, unsigned char id, char * description);

// POSIBLE CAMBIO: ID Y DESCRIPTION METERLOS EN UN STRUCT

// Validates ID
// @param validIDs: ADT to store and access validIDs
// @param id: id we want to validate
bool isValidID(validIDADT validIDs, unsigned char id);

#endif
