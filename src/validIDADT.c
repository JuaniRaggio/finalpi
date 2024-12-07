#include "../include/validIDADT.h"

#define BLOCK 69

struct validIDCDT {
    char ** description;
    ID_TYPE maxID;
    size_t space;
};

validIDADT newValidID(void) {
    validIDADT newValidIDs = calloc(1, sizeof(struct validIDCDT));
    errno = NOERRORSFOUND;
    assert(newValidIDs == NULL, ENOMEM, NULL);
    return newValidIDs;
}

const char * getDescriptionOfID(validIDADT validIDs, ID_TYPE id) {
    return validIDs->description[--id];
}

bool addID(validIDADT validIDs, ID_TYPE id, char * description) {
    assert(validIDs == NULL, NULLARG, false);
    validIDs->maxID = max(validIDs->maxID, id);
    id--;
    errno = NOERRORSFOUND;
    if (validIDs->space <= id) {
        reCalloc((void **)&validIDs->description, sizeof(char *), validIDs->space, id + BLOCK);
        if (errno == ENOMEM) {
            return false;
        }
        validIDs->space = (unsigned int)id + BLOCK;
    } else if (validIDs->description[id] != NULL) {
        return false;
    }
    validIDs->description[id] = malloc(strlen(description) + 1);
    errno = NOERRORSFOUND;
    assert(validIDs->description[id] == NULL, ENOMEM, false);
    strcpy(validIDs->description[id], description);
    return true;
}

bool isValidID(validIDADT validIDs, ID_TYPE id) {
    assert(validIDs == NULL, NULLARG, false);
    if (validIDs->maxID < id) {
        return false;
    }
    return validIDs->description[id - 1] != NULL;
}

int compareIDsDescription(validIDADT validIDs, ID_TYPE id1, ID_TYPE id2) {
    return strncmp(validIDs->description[--id1], validIDs->description[--id2], DESCRIPTION_LEN);
}

int compareIDvsDescription(validIDADT validIDs, ID_TYPE id, char * description){
    return strncmp(validIDs->description[--id], description, DESCRIPTION_LEN);
}

void freeValidIDs(validIDADT validIDs) {
    for (ID_TYPE i = 0; i <= validIDs->maxID; ++i) {
        free(validIDs->description[i]);
    }
    free(validIDs->description);
    free(validIDs);
}

