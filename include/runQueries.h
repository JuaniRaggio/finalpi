#ifndef __RUNQUERIES_H__
#define __RUNQUERIES_H__

#include "agencyTreeADT.h"
#include "processQueries.h"
#include "lib.h"
#include "formats.h"

void runMultithreadedQueries(FILE * queries[QUERIES], agencyTreeADT agency);

void runQueries(agencyTreeADT agency);

#endif

