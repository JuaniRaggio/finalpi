#include <stdbool.h>
#include "../include/agencyTreeADT.h"
#include "../include/validIDADT.h"
#include "diffTreeADT.h"

#ifndef __readData_h_
#define __readData_h_

// Reads line form infractions file and makes it valid
void readInfractions(const char * infractions, validIDADT readInfractions);

// Reads line from tickets file and makes it valid
void readTicketCSV(const char * ticketsFile, validIDADT infractions, agencyTreeADT agencys, diffTreeADT diffs);

#endif

