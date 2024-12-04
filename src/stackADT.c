#include "stackADT.h"
#include <assert.h>
#include <stdlib.h>
#define BLOCK 20

struct stackCDT {
     size_t count;   // Cantidad de elementos en la pila
     elemType * elems;
     size_t size;    // Cantidad de espacio reservado
     compare cmp;
};

stackADT newStack(compare cmp) {
   stackADT ans = calloc(1, sizeof(struct stackCDT));
   ans->cmp = cmp;
   return ans;
}

void push(stackADT stack, elemType elem) {
    // Si no hay lugar lo agrandamos
    if ( stack->count == stack->size ) {
       stack->size += BLOCK;
       stack->elems = realloc(stack->elems, stack->size * sizeof(stack->elems[0]));
    }   
    stack->elems[stack->count++] = elem;
}

elemType pop(stackADT stack) {
   assert(!isEmpty(stack));
   return stack->elems[--stack->count];

   // Variante reusando peek
   elemType ans =peek(stack);
   stack->count--;
   return ans;
}

void freeStack(stackADT stack){
   free(stack->elems);
   free(stack);
}

int isEmpty(const stackADT stack) {
    return stack->count==0;
}

size_t size(const stackADT stack) {
    return stack->count;
}


