#include "../include/runQueries.h"

typedef enum {Q1 = 0, Q2 = 1, Q3 = 2} nQueries;

const char * fileFormat[QUERIES][FH] = 
             {{"query1.csv", "Agency;Infraction;Tickets\n"},
             {"query2.csv", "Agency;Year;Month;YTD\n"},
             {"query3.csv", "Agency;MinAmount;MaxAmount;DiffAmount\n"}};

typedef struct thread_q3 {
    agencyTreeADT agency;
    FILE * query3File;
} thread_q3;

static void * thread_runQuery3(void * r3Arg) {
    thread_q3 * arguments = (thread_q3 *)r3Arg;
    runQuery3(arguments->agency, arguments->query3File);
    return NULL;
}

void runMultithreadedQueries(FILE * queries[QUERIES], agencyTreeADT agency) {
    toBeginAgency(agency);
    toBeginDiff(agency);
    const char * agencyName;
    pthread_t thread;
    thread_q3 query3Arguments = {
        .agency = agency,
        .query3File = queries[Q3],
    };
    // Query3 is independent from agencys Iterator
    pthread_create(&thread, NULL, thread_runQuery3, &query3Arguments);
    while(hasNextAgency(agency) && nextAgency(agency)) {
        agencyName = getNameOfIterator(agency);
        runQuery1(agency, agencyName, queries[Q1]);
        runQuery2(agency, agencyName, queries[Q2]);
    }
    pthread_join(thread, NULL);
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
