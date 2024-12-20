#include "readData.h"

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

void readTicketCSV(const char * tickets, agencyTreeADT agencys) {
    FILE *ticketFile = fopen(tickets, "r");
    errno = NOERRORSFOUND;
    assert(ticketFile == NULL, ENOENT,);
    char line[LINE];
    fgets(line, LINE, ticketFile);
    while (fgets(line, LINE, ticketFile)) {
        processTicket(line, agencys);
    }
    fclose(ticketFile);
    return;
}

