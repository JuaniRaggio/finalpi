#include "../include/runQueries.h"

typedef enum {Q1 = 0, Q2 = 1, Q3 = 2} nQueries;

const char * fileFormat[QUERIES][FH] = 
             {{"query1.csv", "Agency;Infraction;Tickets\n"},
             {"query2.csv", "Agency;Year;Month;YTD\n"},
             {"query3.csv", "Agency;MinAmount;MaxAmount;DiffAmount\n"}};


void runMultithreadedQueries(FILE * queries[QUERIES], agencyTreeADT agency){
    toBeginAgency(agency);
    toBeginDiff(agency);
    const char * agencyName;
    // Query3 is independent from agencys Iterator
    runQuery3(agency, queries[Q3]);
    while(hasNextAgency(agency)) {
        if (!nextAgency(agency)) {
            return;
        }
        agencyName = getNameOfIterator(agency);
        runQuery1(agency, agencyName, queries[Q1]);
        runQuery2(agency, agencyName, queries[Q2]);
    }
}

void runQueries(agencyTreeADT agency){
    FILE * queries[QUERIES];
    for (int queryNumber = 0; queryNumber < QUERIES; queryNumber++) {
        // Inserts filename and header to all queries
        newFile(queries[queryNumber], fileFormat[queryNumber][FILENAME], "w",);
        fprintf(queries[queryNumber], "%s", fileFormat[queryNumber][HEADER]);
    }

    runMultithreadedQueries(queries, agency);

    for (int queryNumber = 0; queryNumber < QUERIES; queryNumber++) {
        fclose(queries[queryNumber]);
    }
}
