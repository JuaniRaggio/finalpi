#include "../include/lib.h"
#include "../include/queries.h"

const char * fileFormat[QUERIES][FH] = 
             {{"query1.csv", "Agency;Infraction;Tickets\n"},
             {"query2.csv", "Agency;Year;Month;YTD\n"},
             {"query3.csv", "Agency;MinAmount;MaxAmount;DiffAmount\n"}};

typedef enum {Q1 = 0, Q2 = 1, Q3 = 2} nQueries;

void runMultithreadedQueries(FILE * queries[QUERIES], agencyTreeADT agency){
    toBeginIterators(agency);

    // Query3 is independent from other
    runQuery3(agency, queries[Q3]);
    while(hasNextAgency(agency)) {
        nextAgency(agency);
        runQuery1(agency, queries[Q1]);
        runQuery2(agency, queries[Q2]);

        toBeginTicket(agency);
        toBeginYear(agency);
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

void runQuery1(agencyTreeADT agency, FILE * q1File){
}

void runQuery2(agencyTreeADT agency, FILE * q2File);

void runQuery3(agencyTreeADT agency, FILE * q3File) {
    while (hasNextDiff(agency)) {
        nDDiff diffData = nextDiff(agency);
        fprintf(q3File, "%s;%lu;%lu;%lu",
                diffData.agencyName, diffData.data->minAmount, diffData.data->maxAmount, diffData.data->minAmount - diffData.data->maxAmount);
        nextDiff(agency);
    }
}

