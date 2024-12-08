#ifndef __RUNQUERIES_H__
#define __RUNQUERIES_H__

#include "agencyTreeADT.h"
#include "processQueries.h"
#include "lib.h"
#include "formats.h"

/// Executes multiple queries 
/// @param queries: array of file pointers where information of queires is going to get stored
/// @param agency: ADT of stored agencies
void runMultithreadedQueries(FILE * queries[QUERIES], agencyTreeADT agency);

/// Executes queries on an agency tree and writes the results in corresponding files
/// @param agency 
void runQueries(agencyTreeADT agency);

#endif

