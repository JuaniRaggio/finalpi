#include "lib.h"

int max(int a, int b) {
    return (a > b) ? a:b;
}

int myStrcpy(char * target, size_t targetDim, const char * source, char * separators) {
    int i = 0;
    for (; source[i] != '\0' && i < targetDim - 1; ++i) {
        if (strchr(separators, source[i]) != NULL) {
            target[i] = '\0';
            return i;
        }
        target[i] = source[i];
    }
    target[i] = '\0';
    return i;
}

unsigned int getLine(char s[], unsigned int maxLength) {
    int c;
    unsigned int n=0;
    while ( (c=getchar()) != EOF && c != '\n') {
        if (n < maxLength) {
            s[n++] = c;
        }    
    }
    s[n] = 0;
    return n;
}

void reCalloc(void ** ptr, size_t sizePtr, size_t oldSize, size_t newSize) {
    if (oldSize >= newSize) {
        return;
    }
    void * tmp = realloc(*ptr, sizePtr * newSize);
    errno = NOERRORSFOUND;
    assert(tmp == NULL, ENOMEM,);
    *ptr = tmp;
    memset((char *)*ptr + oldSize * sizePtr, 0, (newSize - oldSize) * sizePtr);
    return;
}

