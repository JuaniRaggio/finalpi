#ifndef __GENERICSTACKADT_H__
#define __GENERICSTACKADT_H__

#include <stdbool.h>
#include <stdlib.h>
#include "../include/errorManagement.h"
#include "../include/lib.h"

typedef struct genericStackCDT * genericStackADT;
genericStackADT newStack(void);
void push(genericStackADT stack, void * elem);
bool isEmpty(genericStackADT stack);
void * pop(genericStackADT stack);
void freeStack(genericStackADT stack);

#endif

