#include "hashTableADT.h"
#include "bstADT.h"
#include "agencysADT.h"
#include "infractionsADT.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
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
    if (!isValidID(infractionID)) {
        return false;
    } else if (hst->table[idx] == NULL) {
        // Esto iria en insertBST
        /* agencysADT agency = newAgency(agencyName); */
        /* addTicket(agency, infractionID, plate, issueDate, amount); */

        if ((hst->table[idx] = newBST(strcasecmp)) == NULL) {
            return false;
        }
        insertBST(hst->table[idx], agencyName, infractionID, plate, issueDate, amount);

        // Agregar al arbol global con el proposito de mantener las agencias para poder recorrerlas alfabeticamente

        return true;
    }
    return insertBST(hst->table[idx], agencyName, infractionID, plate, issueDate, amount);
}



