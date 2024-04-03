#include "stack.h"
#include <stdlib.h>

STACK* createS() {
    STACK *elem = (STACK*)malloc(sizeof(STACK));
    elem->next = NULL;
    return elem;
}

void push(STACK *S, int value) {
    STACK *elem = (STACK*)malloc(sizeof(STACK));
    elem->value = value;
    elem->next = S->next;
    S->next = elem;
}

int isEmpty(STACK *S) {
    return S->next == NULL;
}

int pop(STACK *S) {
    if (isEmpty(S))
        return -1;
    STACK *first = S->next;
    int val = first->value;
    S->next = first->next;
    free(first);
    return val;
}