#ifndef __VALIDIDADT_H__
#define __VALIDIDADT_H__

#include <stdbool.h>
#include "formats.h"
#include "lib.h"
#include "errorManagement.h"

typedef struct validIDCDT * validIDADT;

// Creates a new ADT to add and ask for valid IDs
validIDADT newValidID(void);

/// Adds a valid ID, if the ID is added successfully returns ture else returns false
/// @param validIDs: ADT to store and access validIDs
/// @param id: Infraction id to add
/// @param description: Description from infraction of id:id
bool addID(validIDADT validIDs, ID_TYPE id, char * description);

/// Validates ID
/// @param validIDs: ADT to store and access validIDs
/// @param id: id we want to validate
bool isValidID(validIDADT validIDs, ID_TYPE id);

/// Compares the description of two ids. Expects valid IDs
/// @param validIDs: ADT to store and access validIDs
/// @param id1, id2: Will be string compared -> id1.description - id2.description
int compareIDsDescription(validIDADT validIDs, ID_TYPE id1, ID_TYPE id2);

/// Returns description associated with a certain ID from validADT
/// @param validIDs: ADT to store and access validIDs 
/// @param id: Infraction id 
const char * getDescriptionOfID(validIDADT validIDs, ID_TYPE id);

/// Compares an ID with a description. Exxpects valid IDs
/// @param validIDs: ADT to store and access validIDs 
/// @param id: Infraction id 
/// @param description: Infraction description 
int compareIDvsDescription(validIDADT validIDs, ID_TYPE id, char * description);

// Frees resources used by ADT
void freeValidIDs(validIDADT validIDs);

#endif
