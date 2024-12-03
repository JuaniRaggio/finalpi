#include <stdbool.h>
#include "../include/agencyTreeADT.h"
#include "../include/validIDADT.h"

#ifndef __readData_h_
#define __readData_h_

void readInfractions(const char * infractions, validIDADT readInfractions);
void readTicketCSV(const char * ticketsFile, validIDADT infractions, agencyTreeADT agencys);

#endif

