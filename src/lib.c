#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/lib.h"
#include "../include/errorManagement.h"

unsigned int getLine(char s[], unsigned int maxLength) {
    int c;
    unsigned int n=0;
    while ( (c=getchar()) != EOF && c != '\n') {
        if ( n < maxLength)
            s[n++] = c;
    }
    s[n] = 0;
    return n;
}

void reCalloc(void ** ptr, size_t sizePtr, size_t oldSize, size_t newSize) {
    if (oldSize >= newSize) return;
    *ptr = realloc(*ptr, sizePtr * newSize);
    errno = NOERRORSFOUND;
    assert(*ptr == NULL, ENOMEM,);
    memset((char *)*ptr + oldSize * sizePtr, 0, (newSize - oldSize) * sizePtr);
}

