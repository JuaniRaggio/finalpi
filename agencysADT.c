#include "agencysADT.h"
#include "hashTableADT.h"
#include <stdlib.h>
#include <stdio.h>

#define PLATE_LENGTH 11

struct agency {
    char * agencyName;
    char plate[PLATE_LENGTH];
    char * issueDate;
    size_t id;
    size_t amount;
};

struct agencysCDT {
    struct agency * agencyData;
    // vector de listas/abroles de infracciones
    size_t minAmount;
    size_t maxAmount;
    size_t tickets;
};

agencysADT newAgency(char * agencyName) {
    agencysADT agency = calloc(1, sizeof(struct agencysCDT));

    return agency;
}

size_t sizeofAgencyCDT(void) {
    return sizeof(struct agencysCDT);
}



