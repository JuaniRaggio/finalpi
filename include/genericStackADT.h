#ifndef __GENERICSTACKADT_H__
#define __GENERICSTACKADT_H__

#include <stdbool.h>
#include "errorManagement.h"
#include "lib.h"

typedef struct genericStackCDT * genericStackADT;

// Creates a new empty stack
genericStackADT newStack(void);

// Push @param elem into the top of the stack
void push(genericStackADT stack, void * elem);

// True if stack is empty
bool isEmpty(genericStackADT stack);

// Pops first element in stack. If agency->stack is empty -> pop returns null
void * pop(genericStackADT stack);

// Frees stack's resources
void freeStack(genericStackADT stack);

#endif

