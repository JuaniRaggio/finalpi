#include "include/agencyTreeADT.h"
#include "include/readData.h"
#include "include/errorManagement.h"
#include "include/runQueries.h"
#include <stdlib.h>

#define EXPECTEDARGS 3

int main(int argc, char ** argv) {
    char exit_status = NOERRORSFOUND;
    if (argc != EXPECTEDARGS) {
        fprintf(stderr, "Invalid arguments, expected: %d, recieved: %d", EXPECTEDARGS, argc);
        exit(EXIT_FAILURE);
    }

    errno = NOERRORSFOUND;
    validIDADT validIDs = newValidID();
    checkErrno(exit_status);

    readInfractions(argv[INFRACTIONARG], validIDs);
    checkErrno(exit_status);

    agencyTreeADT agencyManagement = newAgencys(validIDs);
    checkErrno(exit_status);

    // Hasta aca todo ok

    readTicketCSV(argv[TICKETARG], agencyManagement);
    checkErrno(exit_status);

    runQueries(agencyManagement);
    checkErrno(exit_status);

    freeAgencys(agencyManagement);

    return exit_status;
}

