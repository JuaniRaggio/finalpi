#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/lib.h"
#include "../include/errorManagement.h"

void trimWhitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

char * myStrcpy(char * target, char * source, char * separators) {
    int i = 0;
    for (; source[i] != '\0'; ++i) {
        for (int j = 0; separators[j] != '\0'; ++j) {
            if (source[i] == separators[j]) {
                target[i] = '\0';
                return target;
            }
        }
        target[i] = source[i];
    }
    target[i] = '\0';
    return target;
}

unsigned int getLine(char s[], unsigned int maxLength) {
    int c;
    unsigned int n=0;
    while ( (c=getchar()) != EOF && c != '\n') {
        if (n < maxLength)
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

