#ifndef __readData_h_
#define __readData_h_

#include <stdbool.h>
#include "../include/agencyTreeADT.h"
#include "../include/validIDADT.h"

// Reads line form infractions file and makes it valid
//@param infractions: argument that contains infractions to process.
//@param readInfractions: validIDADT data type where the processed information gets stored.
void readInfractions(const char * infractions, validIDADT readInfractions);

// Reads line from tickets file and makes it valid
//@param ticketsFile: argument that contains tickets to process.
//@param infractions: validIDADT data type where infractions information gets stored.
//@param agencys: agencyTreeADT data type where information about agencies get stored.
//param diffs: diffTreeADT data type where information of amounts is going to get stored. 
void readTicketCSV(const char * ticketsFile, agencyTreeADT agencys);

#endif

