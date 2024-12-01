#include <stdio.h>
#include "getline.h"

unsigned int
getLine(char s[], unsigned int maxLength) {
    int c;
    unsigned int n=0;
    while ( (c=getchar()) != EOF && c != '\n') {
        if ( n < maxLength)
            s[n++] = c;
    }
    s[n] = 0;
    return n;
}