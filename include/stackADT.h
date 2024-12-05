#ifndef __STACKADT_H__
#define __STACKADT_H__

#include <stdio.h>

typedef struct stackCDT * stackADT;

stackADT newStack(size_t sizeofptr);

void push(stackADT stack, void * elem);

void * pop(stackADT stack);

void * peek(stackADT stack);

void freeStack(stackADT stack);

int isEmpty(const stackADT stack);

size_t size(const stackADT stack);

#endif

