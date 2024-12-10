#ifndef __PROCESSDATA_H__
#define __PROCESSDATA_H__

#include "errorManagement.h"
#include "agencyTreeADT.h"
#include "formats.h"

/// Makes valid the infraction at line -> Adds it to validIDADT
/// @param line: String which represents a read line
/// @param infractions: ADT of valid infractions
void processInfraction(char *line, validIDADT infractions);

/// Adds ticket to agencyTreeADT and to diffTreeADT
/// @param line: String which represents a read line
/// @param infractions: ADT of valid infractions
/// @param agencys: ADT of stored agencys
/// @param diffs: ADT of stored diffAmounts
void processTicket(char *line, agencyTreeADT agencys);

#endif

