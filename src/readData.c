#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "../include/readData.h"
#include "../include/validIDADT.h"
#include "../include/agencyTreeADT.h"
#include "../include/errorManagement.h"
#include "../include/lib.h"

static void processInfraction(char *line, validIDADT infractions) {
    char * token = strtok(line, SEPARATOR);
    char * fields[INFRACTIONDIM];
    for (int i = 0; i < INFRACTIONDIM && token != NULL; ++i) {
        fields[INFRACTIONORDER[i]] = token;
        token = strtok(NULL, SEPARATOR);
    }
    addID(infractions, (unsigned char)atoi(fields[ID]), fields[DESCRIPTION]);
    return;
}

static void processTicket(char *line, validIDADT infractions, agencyTreeADT agencys) {
    char * fields[TICKETDIM] = {NULL};
    char * token = strtok(line, SEPARATOR);
    for (int i = 0; i < TICKETDIM && token != NULL; ++i) {
        fields[TICKETORDER[i]] = token;
        token = strtok(NULL, SEPARATOR);
    }
    insertInfraction(agencys, infractions, fields[AGENCY], fields[PLATE], fields[DATE], (unsigned char)atoi(fields[TID]), (size_t)atoi(fields[AMOUNT]));
}

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

void readTicketCSV(const char * ticketsFile, validIDADT infractions, agencyTreeADT agencys) {
    FILE *ticketFile = fopen(ticketsFile, "r");
    errno = NOERRORSFOUND;
    assert(ticketFile == NULL, ENOENT,);
    char line[LINE];
    fgets(line, LINE, ticketFile);
    while (fgets(line, LINE, ticketFile)) {
        processTicket(line, infractions, agencys);
    }
    fclose(ticketFile);
    return;
}

