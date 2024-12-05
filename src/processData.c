#include <stdlib.h>
#include <string.h>
#include "../include/errorManagement.h"
#include "../include/lib.h"
#include "../include/processData.h"

//------------------------- ELMIMINAMOS DIFFTREEADT VER CAMBIOS -------------------------------//

void processInfraction(char *line, validIDADT infractions) {
    char * token = strtok(line, SEPARATOR);
    char * fields[INFRACTIONDIM];
    for (int i = 0; i < INFRACTIONDIM && token != NULL; ++i) {
        fields[INFRACTIONORDER[i]] = token;
        token = strtok(NULL, SEPARATOR);
    }
    addID(infractions, (unsigned char)atoi(fields[ID]), fields[DESCRIPTION]);
    return;
}

void processTicket(char *line, agencyTreeADT agencys) {
    char * fields[TICKETDIM] = {NULL};
    char * token = strtok(line, SEPARATOR);
    for (int i = 0; i < TICKETDIM && token != NULL; ++i) {
        fields[TICKETORDER[i]] = token;
        token = strtok(NULL, SEPARATOR);
    }
    TTicket ticket = {
        .plate = fields[PLATE],
        .issueYear = (size_t)atoll(strtok(fields[DATE], DATESEPARATORS)),
        .issueMonth = (unsigned char)atoi(strtok(NULL, DATESEPARATORS)),
        .infractionID = (size_t)atoll(fields[TID]),
        .amount = (size_t)atoll(fields[AMOUNT]),
    };
    errno = NOERRORSFOUND;
    insertDiff(diffs, &ticket, fields[AGENCY]);
    assert(errno != NOERRORSFOUND, errno,);
    insertAgency(agencys, fields[AGENCY], &ticket);
    assert(errno != NOERRORSFOUND, errno,);
}
