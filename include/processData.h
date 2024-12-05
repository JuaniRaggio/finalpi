#include "../include/agencyTreeADT.h"
#include "../include/formats.h"

#ifndef __PROCESSDATA_H__
#define __PROCESSDATA_H__

// Inserts at diffAmount and agencyTree a valid Ticket
// @param diffAmount: ADT of stored diffAmounts
// @param agencyTree: ADT of stored agencyTree
// @param data: Ticket to insert
void insertBothTrees(agencyTreeADT agencyTree, TTicket data);

// Makes valid the infraction at line -> Adds it to validIDADT
// @param line: String which represents a read line
// @param infractions: ADT of valid infractions
void processInfraction(char *line, validIDADT infractions);

// Adds ticket to agencyTreeADT and to diffTreeADT
// @param line: String which represents a read line
// @param infractions: ADT of valid infractions
// @param agencys: ADT of stored agencys
// @param diffs: ADT of stored diffAmounts
void processTicket(char *line, agencyTreeADT agencys);

#endif

