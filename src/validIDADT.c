#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/lib.h"
#include "../include/errorManagement.h"
#include "../include/validIDADT.h"

#define BLOCK 69

struct validIDCDT {
    char ** description;
    unsigned char maxID;
    unsigned char space;
};

validIDADT newValidID(void) {
    validIDADT newValidIDs = calloc(1, sizeof(struct validIDCDT));
    assert(newValidIDs == NULL, ENOMEM, NULL);
    return newValidIDs;
}

static size_t max(unsigned char a, unsigned char b) {
    return a > b ? a:b;
}

bool addID(validIDADT validIDs, unsigned char id, char * description) {
    validIDs->maxID = max(validIDs->maxID, id);
    id--;
    errno = 0;
    if (validIDs->space <= id) {
        reCalloc((void **)&validIDs->description, sizeof(char *), validIDs->space, id + BLOCK);
        if (errno == ENOMEM) {
            return false;
        }
        validIDs->space = id + BLOCK;
    }
    validIDs->description[id] = malloc(strlen(description) + 1);
    assert(validIDs->description[id] == NULL, ENOMEM, false);
    strcpy(validIDs->description[id], description);
    return true;
}

bool isValidID(validIDADT validIDs, unsigned char id) {
    if (validIDs->maxID < id) {
        return false;
    }
    return validIDs->description[id - 1] != NULL;
}

