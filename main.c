#include "include/agencyTreeADT.h"
#include "include/validIDADT.h"
#include "include/queries.h"
#include "include/readData.h"
#include "include/formats.h"
#include "include/errorManagement.h"
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

    readTicketCSV(argv[TICKETARG], agencyManagement);
    checkErrno(exit_status);

    runMultithreadedQueries(agencyManagement);
    checkErrno(exit_status);

    return exit_status;
}

