#include "../include/genericStackADT.h"

#define STACKBLOCK 20
#define NOELEMENTSLEFT 0

struct genericStackCDT {
    void ** elements;
    size_t last;
};

genericStackADT newStack(void) {
    genericStackADT ans = calloc(1, sizeof(struct genericStackCDT));
    assert(ans == NULL, NULLARG, NULL);
    return ans;
}

void push(genericStackADT stack, void * elem) {
    if (stack->last % STACKBLOCK == 0) {
        stack->elements = realloc(stack->elements, (stack->last + STACKBLOCK) * sizeof(void *));
        assert(stack->elements == NULL, ENOMEM,);
    }
    stack->elements[stack->last++] = elem;
}

bool isEmpty(genericStackADT stack) {
    return stack->last == NOELEMENTSLEFT;
}

void * pop(genericStackADT stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->elements[--stack->last];
}

void freeStack(genericStackADT stack) {
    free(stack->elements);
    free(stack);
}

