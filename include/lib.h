#include <stdio.h>

#ifndef __LIB_H__
#define __LIB_H__

// Copys until a separator is found or targetDim is reached
char * myStrcpy(char * target, size_t targetDim, char * source, char * separators);

// Resizes pointer and fills with zero
void reCalloc(void ** ptr, size_t sizePtr, size_t oldSize, size_t newSize);

// Reads line and appends it to s
unsigned int getLine(char s[], unsigned int maxLength);

// Deletes extra whitespaces
void trimWhitespace(char *str);

#endif

