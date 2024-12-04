#include <stdio.h>

typedef int elemType;

// Tipo que define a la funcion de comparacion
typedef int (*compare)(elemType, elemType);


/*
typedef struct point {
    double x;
    double y=;
} elemType;
*/

typedef struct stackCDT * stackADT;

stackADT newStack(compare fn);

void push(stackADT stack, elemType elem);

elemType pop(stackADT stack);

void freeStack(stackADT stack);

int isEmpty(const stackADT stack);

// Retorna la cantidad de elementos en la pila
size_t size(const stackADT stack);