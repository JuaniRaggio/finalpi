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
    size_t minAmount;
    size_t maxAmount;
    size_t tickets;
};



