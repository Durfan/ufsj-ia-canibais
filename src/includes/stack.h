

typedef struct cell_t{
	int key;
	struct cell_t *next;
} Cell;

typedef struct {
	Cell *first, *last;
} Stack;

Stack *initStack();
int push(Stack *stack);
void pop(Stack *stack, int item);
void prtStack(Stack *stack);
int stackIsEmpty(Stack *stack);
int itemExist(Stack *stack, int item);
void destroyStack(Stack *stack);
