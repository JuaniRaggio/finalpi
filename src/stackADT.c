#include "../include/stackADT.h"
#include "../include/errorManagement.h"
#include <stdlib.h>
#include <string.h>
#define BLOCK 20

struct stackCDT {
    void ** elems;
    size_t count;
    size_t size;
    size_t sizeofptr;
};

stackADT newStack(size_t sizeofptr) {
    stackADT ans = calloc(1, sizeof(struct stackCDT));
    assert(ans == NULL, NULLARG, NULL);
    return ans;
}

void push(stackADT stack, void * elem) {
    assert(!isEmpty(stack) || elem == NULL, NULLARG,);
    if (stack->count == stack->size) {
        stack->size += BLOCK;
        void ** tmp = realloc(stack->elems, stack->size * sizeof(void *));
        assert(tmp == NULL, ENOMEM,);
        stack->elems = tmp;
    }   
    memcpy((char *)stack->elems + stack->sizeofptr * (stack->count++), elem, stack->sizeofptr);
}

void * pop(stackADT stack) {
    assert(!isEmpty(stack), NULLARG, NULL);
    return stack->elems[--stack->count];
}

void * peek(stackADT stack) {
    assert(!isEmpty(stack), NULLARG, NULL);
    return (char *)stack->elems + (stack->count - 1) * stack->sizeofptr;
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


