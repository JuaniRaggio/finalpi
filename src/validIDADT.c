#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/lib.h"
#include "../include/errorManagement.h"
#include "../include/validIDADT.h"
#include "../include/formats.h"

#define BLOCK 69

struct validIDCDT {
    char ** description;
    unsigned char maxID;
    unsigned char space;
};

validIDADT newValidID(void) {
    validIDADT newValidIDs = calloc(1, sizeof(struct validIDCDT));
    errno = NOERRORSFOUND;
    assert(newValidIDs == NULL, ENOMEM, NULL);
    return newValidIDs;
}

bool addID(validIDADT validIDs, unsigned char id, char * description) {
    assert(validIDs == NULL, NULLARG, false);
    validIDs->maxID = max(validIDs->maxID, id);
    id--;
    errno = NOERRORSFOUND;
    if (validIDs->space <= id) {
        reCalloc((void **)&validIDs->description, sizeof(char *), validIDs->space, id + BLOCK);
        if (errno == ENOMEM) {
            return false;
        }
        validIDs->space = id + BLOCK;
    } else if (validIDs->description[id] != NULL) {
        return false;
    }
    validIDs->description[id] = malloc(strlen(description) + 1);
    errno = NOERRORSFOUND;
    assert(validIDs->description[id] == NULL, ENOMEM, false);
    myStrcpy(validIDs->description[id], DESCRIPTION_LEN, description, SEPARATOR);
    return true;
}

bool isValidID(validIDADT validIDs, unsigned char id) {
    assert(validIDs == NULL, NULLARG, false);
    if (validIDs->maxID < id) {
        return false;
    }
    return validIDs->description[id - 1] != NULL;
}

int compareIDsDescription(validIDADT validIDs, unsigned char id1, unsigned char id2) {
    return strncmp(validIDs->description[--id1], validIDs->description[--id2], DESCRIPTION_LEN);
}



