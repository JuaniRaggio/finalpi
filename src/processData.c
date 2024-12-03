#include <stdlib.h>
#include <string.h>
#include "../include/lib.h"
#include "../include/processData.h"

void insertBothTrees (diffTreeADT diffAmount, agencyTreeADT agencyTree, TTicket data) {
}

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

void processTicket(char *line, validIDADT infractions, agencyTreeADT agencys, diffTreeADT diffs) {
    char * fields[TICKETDIM] = {NULL};
    char * token = strtok(line, SEPARATOR);
    for (int i = 0; i < TICKETDIM && token != NULL; ++i) {
        fields[TICKETORDER[i]] = token;
        token = strtok(NULL, SEPARATOR);
    }
    // Agregar funcion de diffamount con threads
    insertInfraction(agencys, infractions, fields[AGENCY], fields[PLATE], fields[DATE], (unsigned char)atoi(fields[TID]), (size_t)atoi(fields[AMOUNT]));
    return;
}
