#include <stdlib.h>
#include "../include/formats.h"
#include "../include/lib.h"
#include "../include/diffTreeADT.h"

typedef struct diffNode {
    char agencyName[AGENCY_LEN];
    size_t diffAmount;
    size_t minAmount;
    size_t maxAmount;
} TDiff;

struct diffTreeCDT {
    TDiff * root;
    TDiff * iterator;
};

diffTreeADT newDiff();

