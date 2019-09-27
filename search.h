

int **depthSearch(State start, State *hashmap);
int expandAndStack(State state, State *hashmap, Stack *stack);
void constructionSolution(State start, int actualNode, State *hashmap, int **graph);
