#include "./includes/main.h"

Stack *initStack(void) {
	Stack *stack = malloc(sizeof(Stack));
	assert(stack);

	stack->top = NULL;
	stack->size = 0;

	return stack;
}

void pshStack(Stack *stack, int key) {
	Node *node = malloc(sizeof(Node));
	assert(node);

	node->key = key;
	node->next = stack->top;
	stack->top = node;
	stack->size++;
}

int popStack(Stack *stack) {
	if (stack->top == NULL)
		return;
	Node *delNode = stack->top;
	stack->top = stack->top->next;
	stack->size--;
	int key = delNode->key;
	free(delNode);
	return key;
}

void prtStack(Stack *stack){
	if (stack->top == NULL)
		return;

	Node *node = stack->top;
	printf("STACK: [");
	while (node != NULL){
		printf(" %d,", node->key);
		node = node->next;
	}
	printf(" ]\n");
}

bool stkEmpty(Stack *stack) {
	return (stack->top == NULL);
}

void delStack(Stack *stack) {
	if (stack->top == NULL) {
		free(stack);
		return;
	}

	Node *del;
	while (stack->top != NULL) {
        del = stack->top;
        stack->top = stack->top->next;
        free(del);
    }
    free(stack);
}
