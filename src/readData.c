#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "../include/formats.h"
#include "../include/readData.h"
#include "../include/processData.h"
#include "../include/validIDADT.h"
#include "../include/agencyTreeADT.h"
#include "../include/errorManagement.h"
#include "../include/lib.h"

void readInfractions(const char * infractions, validIDADT readInfractions) {
    FILE * infractionFile = fopen(infractions, "r");
    errno = NOERRORSFOUND;
    assert(infractionFile == NULL, ENOENT,);
    char line[LINE];
    fgets(line, LINE, infractionFile);
    while (fgets(line, LINE, infractionFile)) {
        processInfraction(line, readInfractions);
    }
    fclose(infractionFile);
    return;
}

void readTicketCSV(const char * tickets, validIDADT infractions, agencyTreeADT agencys, diffTreeADT diffs) {
    FILE *ticketFile = fopen(tickets, "r");
    errno = NOERRORSFOUND;
    assert(ticketFile == NULL, ENOENT,);
    char line[LINE];
    fgets(line, LINE, ticketFile);
    while (fgets(line, LINE, ticketFile)) {
        processTicket(line, infractions, agencys, diffs);
    }
    fclose(ticketFile);
    return;
}

