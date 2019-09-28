#ifndef _STACK_H
#define _STACK_H

typedef struct node_t {
	int key;
	struct node_t *next;
} Node;

typedef struct stack_t {
	int size;
	struct node_t *top;
} Stack;

Stack *initStack();
void pshStack(Stack *stack, int key);
int popStack(Stack *stack);
void prtStack(Stack *stack);
bool stkEmpty(Stack *stack);
void delStack(Stack *stack);

#endif // _STACK_H
