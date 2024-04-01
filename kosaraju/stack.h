

#ifndef NSU_LEARNING_STACK_H
#define NSU_LEARNING_STACK_H

typedef struct stack{
int value;
struct stack *next;
}STACK;
void push(STACK *S, int value);
STACK* createS();
#endif //NSU_LEARNING_STACK_H
