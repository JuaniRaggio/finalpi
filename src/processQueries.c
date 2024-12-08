#include "../include/processQueries.h"

#define NULLAMOUNT 0

void runQuery1(agencyTreeADT agency, const char * agencyName, FILE * q1File) {
    toBeginTicket(agency);
    while (hasNextTicket(agency)) {
        DTicket ticketData = nextTicket(agency);
        const char * desc = getDescriptionOfidAtAgency(agency, ticketData.id);
        /* if (desc == NULL) printf("El nombre de la descripcion del iterador es NULL, cuando el nombre de la agencia es: %s y el id es:%u \n", agencyName, ticketData.id); */
        fprintf(q1File, "%s;%s;%lu\n", agencyName, desc, ticketData.units);
    }
}

void runQuery2(agencyTreeADT agency, const char * agencyName, FILE * q2File) {
    toBeginYear(agency);
    while (hasNextYear(agency)) {
        DYear yearData = nextYear(agency);
        /* printf("Entro al if -> totalCollected no es 0\n"); */
        size_t tillMonthx = 0;
        for (unsigned char month = 0; month < MONTHS; ++month) {
            if (yearData.collected[month] != NULLAMOUNT) {
                tillMonthx += yearData.collected[month];
                fprintf(q2File, "%s;%lu;%u;%lu\n", agencyName, yearData.yearN, month + 1, tillMonthx);
                /* printf("%s;%lu;%u;%lu\n", agencyName, yearData.yearN, month + 1, yearData.collected[month]); */
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

