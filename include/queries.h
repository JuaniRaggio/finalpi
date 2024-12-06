#ifndef __QUERIES_H__
#define __QUERIES_H__

#include "../include/agencyTreeADT.h"

void runQueries(agencyTreeADT agency);
void runMultithreadedQueries(FILE * queries[QUERIES], agencyTreeADT agencys);
void runQuery1(agencyTreeADT, FILE*);
void runQuery2(agencyTreeADT, FILE*);
void runQuery3(agencyTreeADT, FILE*);

#endif

