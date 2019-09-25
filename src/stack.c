#include "./includes/main.h"


Stack *initStack(){
	Stack *stack = (Stack*)malloc(sizeof(Stack));
	stack->first = NULL;
	stack->last = NULL;
	return stack;
}



int push(Stack *stack){
	int value;
	if(stack->first == NULL){
		printf("\nEmpty Stack.\n");
		return -1;
	}
	Cell *aux = stack->first;
	value = aux->key;
	stack->first = aux->next;
	free(aux);
	return value;
}


void pop(Stack *stack, int item){
	Cell *newHead = (Cell*)malloc(sizeof(Cell));
	if(stack->first == NULL){
		stack->last = newHead;
	}
	newHead->next = stack->first;
	newHead->key = item;
	stack->first = newHead;
}

void prtStack(Stack *stack){
	if(stack->first == NULL){
		printf("\nEmpty Stack.\n");
		return;
	}
	Cell *cell = stack->first;
	printf("\nSTACK: [");
	while(cell != NULL){
		printf("%d  ", cell->key);
		cell = cell->next;
	}
	printf("]\n");
}

int stackIsEmpty(Stack *stack){
	if(stack->first == NULL) return 1;
	else return 0;
}

int itemExist(Stack *stack, int item){
	Cell *cell = stack->first;
	while(cell != NULL){
		if(cell->key == item){
			return 1;
		}
		cell = cell->next;
	}
	return 0;
}
