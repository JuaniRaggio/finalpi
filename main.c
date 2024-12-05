#include "include/agencyTreeADT.h"
#include "include/diffTreeADT.h"
#include "include/validIDADT.h"
#include "include/queries.h"
#include "include/readData.h"
#include "include/formats.h"
#include "include/errorManagement.h"
#include <stdlib.h>

#define EXPECTEDARGS 3
typedef void * (*newADT)(void);
void * createNew(newADT);

int main(int argc, char ** argv) {
    if (argc != EXPECTEDARGS) {
        fprintf(stderr, "Invalid arguments, expected: %d, recieved: %d", EXPECTEDARGS, argc);
        exit(EXIT_FAILURE);
    }
    validIDADT validIDs = createNew((newADT)newValidID);
    readInfractions(argv[INFRACTIONARG], validIDs);
    agencyTreeADT agencyManagement = newAgencys(validIDs);
    assert(agencyManagement == NULL, errno, ENOMEM);
    diffTreeADT diffAmounts = createNew((newADT)newDiff);
    readTicketCSV(argv[TICKETARG], validIDs, agencyManagement, diffAmounts);
    runMultithreadedQueries(validIDs, diffAmounts, agencyManagement);
    return EXIT_SUCCESS;
}

void * createNew(newADT newFunction) {
    void * ADT = newFunction();
    checkErrno();
    return ADT;
}

