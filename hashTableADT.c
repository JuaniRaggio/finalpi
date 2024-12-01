#include "hashTableADT.h"
#include "bstADT.h"
#include "agencysADT.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 500000
#define OFFSET_BASIS 5381

struct hashTableCDT {
    bstADT table[TABLE_SIZE];
    size_t used;
};

unsigned long hashFunction(unsigned char *str) {
    unsigned long hash = OFFSET_BASIS;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // 5 is an optimization
    }
    return hash;
}

hashTableADT newHashTable(void) {
    return calloc(1, sizeof(struct hashTableCDT));
}

bool insertHT(hashTableADT hst, char * agencyName, char * infractionID, char plate[], char * issueDate, size_t amount) {
    unsigned long idx = hashFunction((unsigned char *)agencyName) % TABLE_SIZE;
    if (hst->table[idx] == NULL) {
        hst->table[idx] = newBST(sizeof(struct agencysCDT), strcasecmp);
        agencysADT agency = newAgency(agencyName);
        addTicket(agency, infractionID, plate, issueDate, amount);
        insertBST(hst->table[idx], agency);
    } else if ()
}



