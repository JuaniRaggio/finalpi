#include "processData.h"

void processInfraction(char *line, validIDADT infractions) {
    char * token = strtok(line, SEPARATOR);
    char * fields[INFRACTIONDIM];
    for (int i = 0; i < INFRACTIONDIM && token != NULL; ++i) {
        // fields[i] will end in a separator not a '\0'
        fields[INFRACTIONORDER[i]] = token;
        token = strtok(NULL, SEPARATOR);
    }

    // OJO con el  (unsignec char) atoi

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
        .issueYear = (size_t)atoi(fields[DATE]),
        .issueMonth = (unsigned char)atoi(fields[DATE] + YEAR_LEN + 1),
        .infractionID = (ID_TYPE)atoi(fields[TID]),
        .amount = (size_t)atoll(fields[AMOUNT]),
    };
    insertAgency(agencys, fields[AGENCY], &ticket);
    assert(errno != NOERRORSFOUND, errno,);
}
