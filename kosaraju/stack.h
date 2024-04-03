#ifndef NSU_LEARNING_STACK_H
#define NSU_LEARNING_STACK_H

typedef struct stack{
    int value;
    struct stack *next;
}STACK;

STACK* createS();
void push(STACK *S, int value);
int isEmpty(STACK *S);
int pop(STACK *S);

#endif //NSU_LEARNING_STACK_H
