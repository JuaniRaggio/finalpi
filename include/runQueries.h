#ifndef __RUNQUERIES_H__
#define __RUNQUERIES_H__

#include "agencyTreeADT.h"
#include "lib.h"
#include "formats.h"

/// Function that stores all the generated information of query 1 in a .csv file
/// @param agency: ADT of stored agencies
/// @param agencyName: agency name 
/// @param q1File: file where processed information is going to be stored
void runQuery1(agencyTreeADT agency, const char * agencyName, FILE * q1File);

/// Function that stores all the generated information of query 2 in a .csv file
/// @param agency: ADT of stored agencies
/// @param agencyName: agency name 
/// @param q2File: file where processed information is going to be stored
void runQuery2(agencyTreeADT agency, const char * agencyName, FILE * q2File);

/// Function that stores all the generated information of query 3 in a .csv file
/// @param agency: ADT of stored agencies
/// @param agencyName: agency name 
/// @param q3File: file where processed information is going to be stored
void runQuery3(agencyTreeADT agency, FILE * q3File);

/// Executes queries on an agency tree and writes the results in corresponding files
/// @param agency: ADT of stored agencies  
void runQueries(agencyTreeADT agency);

#endif

