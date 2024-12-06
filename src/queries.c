#include "../include/lib.h"
#include "../include/queries.h"


void runMultithreadedQueries(agencyTreeADT agency){
    toBeginAgency(agency);
    char * agencyName = NULL;

    while(hasNextAgency(agency)) {
        agencyName = nextAgency(agency);
        runQuery1(agency,agencyName);
        runQuery2(agency,agencyName);
        runQuery3(agency,agencyName);
    }
}

void runQueries(agencyTreeADT agency){
    FILE * queries[QUERIES];
    for (int queryNumber = 0; queryNumber < QUERIES; queryNumber++) {
        newFile(queries[queryNumber], fileFormat[queryNumber][FILENAME], "w",);
        fprintf(queries[queryNumber], "%s", fileFormat[queryNumber][HEADER]);
    }

    runMultithreadedQueries(agency);

    for (int queryNumber = 0; queryNumber < QUERIES; queryNumber++) {
        fclose(queries[queryNumber]);
    }
}

void runQuery1(agencyTreeADT agency, char * agencyName){
    
}


