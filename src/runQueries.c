#include "runQueries.h"

typedef enum {Q1 = 0, Q2 = 1, Q3 = 2} nQueries;

const char * fileFormat[QUERIES][FH] = 
             {{"query1.csv", "Agency;Infraction;Tickets\n"},
             {"query2.csv", "Agency;Year;Month;YTD\n"},
             {"query3.csv", "Agency;MinAmount;MaxAmount;DiffAmount\n"}};

#define NULLAMOUNT 0

// Returns true if a is (DYear){0}
static bool compareYNULL(DYear a);
// Returns true if a is (DTicket){0}
static bool compareTNULL(DTicket a);

static bool compareTNULL(DTicket a) {
    return a.units == 0 && a.id == 0;
}

void runQuery1(agencyTreeADT agency, const char * agencyName, FILE * q1File) {
    toBeginTicket(agency);
    DTicket ticketData;
    while (hasNextTicket(agency) && !compareTNULL(ticketData = nextTicket(agency))){
        const char * desc = getDescriptionOfidAtAgency(agency, ticketData.id);
        fprintf(q1File, "%s;%s;%lu\n", agencyName, desc, ticketData.units);
    }
}

static bool compareYNULL(DYear a) {
    return a.totalCollected == 0 && a.yearN == 0;
}

void runQuery2(agencyTreeADT agency, const char * agencyName, FILE * q2File) {
    toBeginYear(agency);
    DYear yearData;
    while (hasNextYear(agency) && !compareYNULL(yearData = nextYear(agency))) {
        size_t tillMonthx = 0;
        for (unsigned char month = 0; month < MONTHS; ++month) {
            if (yearData.collected[month] != NULLAMOUNT) {
                tillMonthx += yearData.collected[month];
                fprintf(q2File, "%s;%lu;%u;%lu\n", agencyName, yearData.yearN, month + 1, tillMonthx);
            }
        }
    }
}

void runQuery3(agencyTreeADT agency, FILE * q3File) {
    while (hasNextDiff(agency)) {
        nDDiff diffData = nextDiff(agency);
        fprintf(q3File, "%s;%lu;%lu;%lu\n",
                diffData.agencyName, diffData.data->minAmount, diffData.data->maxAmount, diffData.data->maxAmount - diffData.data->minAmount);
    }
}

void runQueries(agencyTreeADT agency){
    FILE * queries[QUERIES];
    for (int queryNumber = 0; queryNumber < QUERIES; queryNumber++) {
        // Inserts filename and header to all queries
        newFile(queries[queryNumber], fileFormat[queryNumber][FILENAME], "w",);
        fprintf(queries[queryNumber], "%s", fileFormat[queryNumber][HEADER]);
    }
    toBeginAgency(agency);
    toBeginDiff(agency);
    const char * agencyName;
    runQuery3(agency, queries[Q3]);
    while(hasNextAgency(agency) && nextAgency(agency)) {
        agencyName = getNameOfIterator(agency);
        runQuery1(agency, agencyName, queries[Q1]);
        runQuery2(agency, agencyName, queries[Q2]);
    }
    for (int queryNumber = 0; queryNumber < QUERIES; queryNumber++) {
        fclose(queries[queryNumber]);
    }
}

