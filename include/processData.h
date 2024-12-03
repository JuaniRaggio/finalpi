#include "../include/diffTreeADT.h"
#include "../include/agencyTreeADT.h"
#include "../include/formats.h"

#ifndef __PROCESSDATA_H__
#define __PROCESSDATA_H__

void insertBothTrees(diffTreeADT diffAmount, agencyTreeADT agencyTree, TTicket data);

void processInfraction(char *line, validIDADT infractions);

void processTicket(char *line, validIDADT infractions, agencyTreeADT agencys, diffTreeADT diffs);

#endif

