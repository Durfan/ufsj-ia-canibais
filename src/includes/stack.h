

typedef struct{
	int key;
	struct Cell *next;
} Cell;

typedef struct {
    struct Cell *first;
	struct Cell *last;
} Stack;

Stack *initStack();
int push(Stack *stack);
void pop(Stack *stack, int item);
void prtStack(Stack *stack);
int stackIsEmpty(Stack *stack);
int itemExist(Stack *stack, int item);
