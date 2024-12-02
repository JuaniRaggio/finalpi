#include <stdio.h>
#ifndef __LIB_H__
#define __LIB_H__

void reCalloc(void ** ptr, size_t sizePtr, size_t oldSize, size_t newSize);
unsigned int getLine(char s[], unsigned int maxLength);
#endif

