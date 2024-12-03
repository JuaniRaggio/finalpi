#include <stdbool.h>
#include "../include/agencyTreeADT.h"
#include "../include/validIDADT.h"

#ifndef __readData_h_
#define __readData_h_

// Reads line form infractions file and makes it valid
void readInfractions(const char * infractions, validIDADT readInfractions);

// Reads line from tickets file and makes it valid
void readTicketCSV(const char * ticketsFile, validIDADT infractions, agencyTreeADT agencys);

// Insert node in both trees finish when both nodes got inserted
//void insertBothTrees(diffTreeADT diffAmount,agencyTreeADT agencyTree, char agecyName[AGENCY_LEN], char plate[PLATE_LEN], char descrption[DESCRIPTION_LEN], size_t amount, unsigned char id);

#endif

