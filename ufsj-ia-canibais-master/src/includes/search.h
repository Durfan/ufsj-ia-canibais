

void expandAndStack(State state, State *hashmap, Stack *stack, int *numJumps);
void constructionSolution(State start, int actualNode, State *hashmap, int **graph);
int **depthFirstSearch(State start, State *hashmap);
int **limitedDepthSearch(State start, State *hashmap, int limit);
int **breadthFirstSearch(State start, State *hashmap, State end);
int **bidirectionalBredthSearch(State start, State end, State *hashmapTop, State *hashmapBot);
