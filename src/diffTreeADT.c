#include <stdlib.h>
#include "../include/validIDADT.h"
#include "../include/formats.h"
#include "../include/lib.h"
#include "../include/diffTreeADT.h"


typedef struct diffNode {
    DDiff diffData;
    struct diffNode * next;
} TDiff;

struct diffTreeCDT {
    TDiff * root;
    TDiff * iterator;
    validIDADT validIDs;
};

diffTreeADT newDiff(validIDADT validIDs);

