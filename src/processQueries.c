#include "../include/processQueries.h"

#define NULLAMOUNT 0


void runQuery1(agencyTreeADT agency, const char * agencyName, FILE * q1File) {
    while (hasNextTicket(agency)) {
        DTicket ticketData = nextTicket(agency);
        fprintf(q1File, "%s;%s;%lu\n", agencyName, getDescriptionOfIterator(agency), ticketData.units);
        nextTicket(agency);
    }
}

void runQuery2(agencyTreeADT agency, const char * agencyName, FILE * q2File) {
    while (hasNextYear(agency)) {
        DYear yearData = nextYear(agency);
        if (yearData.totalCollected != NULLAMOUNT) {
            for (unsigned char month = 0; month < MONTHS; ++month) {
                fprintf(q2File, "%s;%lu;%u;%lu\n", agencyName, yearData.yearN, month + 1, yearData.collected[month]);
            }
        }
    }
}

void runQuery3(agencyTreeADT agency, FILE * q3File) {
    while (hasNextDiff(agency)) {
        nDDiff diffData = nextDiff(agency);
        fprintf(q3File, "%s;%lu;%lu;%lu\n",
                diffData.agencyName, diffData.data->minAmount, diffData.data->maxAmount, diffData.data->maxAmount - diffData.data->minAmount);
        nextDiff(agency);
    }
}

