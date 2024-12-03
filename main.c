#include "include/agencyTreeADT.h"
#include "include/diffTreeADT.h"
#include "include/queries.h"
#include "include/readData.h"
#include "include/validIDADT.h"
#include "include/lib.h"
#include "include/formats.h"
#include <stdio.h>
#include <errno.h>

int main(int argc, char ** argv) {
    validIDADT validIDs = newValidID();
    if (errno == ENOMEM) {
        exit(1);
    }
    readInfractions(argv[INFRACTIONARG], validIDs);
    agencyTreeADT agencyManagement = newAgencys();
    diffTreeADT diffAmounts = newDiff();
    readTicketCSV(argv[TICKETARG], validIDs, agencyManagement, diffAmounts);
    runMultithreadedQueries(validIDs, diffAmounts, agencyManagement);
    return 0;
}

