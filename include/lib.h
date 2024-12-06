#ifndef __LIB_H__
#define __LIB_H__

#include <stdio.h>
#include "errorManagement.h"

#define newFile(ptr, name, permission, retValue){ \
    ptr = fopen(name, permission); \
    assert(ptr == NULL, ENOENT, retValue); \
}


// Copys until a separator is found or targetDim is reached
// @param target: Copys into target
// @param targetDim: target dimension
// @param source: Copys from source
// @param separators
char * myStrcpy(char * target, size_t targetDim, const char * source, char * separators);

int myStrncmp(const char * target, const char * source, char * separators, size_t n);

// Resizes pointer and fills with zero
// @param ptr: Pointer to resize
// @param sizePtr: size of Pointer type
// @param oldSize: Old length of ptr
// @param newSize: New length of ptr
void reCalloc(void ** ptr, size_t sizePtr, size_t oldSize, size_t newSize);

// Reads line and appends it to s
// @param s: Vector of maxLength characters
// @param maxLength: Length of s
unsigned int getLine(char s[], unsigned int maxLength);

// Deletes extra whitespaces
// @param str: String to trim
void trimWhitespace(char *str);

int max(int a, int b);

#endif

