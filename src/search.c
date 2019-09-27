#include "./includes/main.h"


void expandAndStack(State state, State *hashmap, Stack *stack, int *numJumps) {
	State child;
	int m,c,parent = hashKey(state);
	int boat[][2] ={{2,0},{0,2},{1,1},{1,0},{0,1}};

	for (int i=0; i < 5; i++) {
		m = boat[i][0];
		c = boat[i][1];
		child = state;
		child.parent = &hashmap[parent];
		if (feasible(child,m,c)) {
			child = carry(child,m,c);
			child = isDinner(child);
			child.src = parent;
	//		printf(" %d", child.src);
			if (!mapped(child,hashmap)  && !child.dinner){
				numJumps[hashKey(child)] = numJumps[hashKey(*child.parent)]+1;
				addState(child,hashmap);
				pshStack(stack, hashKey(child));
			}
		}
	}
}


void constructionSolution(State start, int actualNode, State *hashmap, int **graph){
	State *parent = hashmap[actualNode].parent;

	while (hashKey(*parent) != hashKey(start)) {
		graph[hashKey(*parent)][actualNode] = 1;
		actualNode = hashKey(*parent);
		parent = hashmap[actualNode].parent;
	}
 	graph[hashKey(*parent)][actualNode] = 1;
}


int **depthFirstSearch(State start, State *hashmap){
	int *numJumps = calloc(MAPSIZE, sizeof(int));
    Stack *stack = initStack();

	// Search
    addState(start, hashmap);
    expandAndStack(start, hashmap, stack, numJumps);
	int **graph = iniGraph();
    int actualNode;
	while (!stkEmpty(stack)) {

        actualNode = popStack(stack);
        if (hashmap[actualNode].m == 0 && hashmap[actualNode].c == 0){
			gGraph(hashmap,graph);
			delStack(stack);
			return graph;
       }
	   else {
			expandAndStack(hashmap[actualNode], hashmap, stack, numJumps);
		}
    }
	free(numJumps);
	gGraph(hashmap,graph);
	return graph;
}


int **limitedDepthSearch(State start, State *hashmap, int limit){
	int *numJumps = calloc(MAPSIZE, sizeof(int));
    Stack *stack = initStack();

    addState(start, hashmap);
    expandAndStack(start, hashmap, stack, numJumps);

    int actualNode;
	int **graph = iniGraph();
	while (!stkEmpty(stack)) {

        actualNode = popStack(stack);
        if (hashmap[actualNode].m == 0 && hashmap[actualNode].c == 0){
			gGraph(hashmap,graph);
			delStack(stack);
			return graph;
       }
	   else if(numJumps[actualNode] < limit){
			expandAndStack(hashmap[actualNode], hashmap, stack, numJumps);
		}
    }
	free(numJumps);
	gGraph(hashmap,graph);
	return graph;
}


int **breadthFirstSearch(State start, State *hashmap, State end){
	int *numJumps = calloc(MAPSIZE, sizeof(int));

	Stack *stack = initStack();
	addState(start, hashmap);
	int node = hashKey(start);
	int **graph = iniGraph();
	for(int i = 0; i < MAPSIZE; i++){
		expandAndStack(hashmap[node], hashmap, stack, numJumps);
		while(!stkEmpty(stack)){
			node = popStack(stack);
			if(node == hashKey(end)){
				gGraph(hashmap,graph);
				delStack(stack);
				return graph;
			}
		}
	}
	free(numJumps);
	gGraph(hashmap,graph);
	return graph;
}


int **bidirectionalBredthSearch(State start, State end, State *hashmapTop, State *hashmapBot){
	int *numJumps = calloc(MAPSIZE, sizeof(int));

	Stack *stackTop = initStack();
	Stack *stackBot = initStack();

	addState(start, hashmapTop);
	addState(end, hashmapBot);

	int nodeTop = hashKey(start), nodeBot = hashKey(end);
	int **graph = iniGraph();

	for(int i = 0; i < MAPSIZE; i++){
		expandAndStack(hashmapTop[nodeTop], hashmapTop, stackTop, numJumps);
		expandAndStack(hashmapBot[nodeBot], hashmapBot, stackBot, numJumps);
		while(!stkEmpty(stackTop)){
			nodeTop = popStack(stackTop);
			if(mapped(hashmapTop[nodeTop], hashmapBot)){
				gGraph(hashmapTop,graph);
				gGraph(hashmapBot,graph);
				delStack(stackTop);
				delStack(stackBot);
				return graph;
			}
		}
		while(!stkEmpty(stackBot)){
			nodeBot = popStack(stackBot);
			if(mapped(hashmapBot[nodeBot], hashmapTop)){
				gGraph(hashmapTop,graph);
				gGraph(hashmapBot,graph);
				delStack(stackTop);
				delStack(stackBot);
				return graph;
			}
		}
	}
	free(numJumps);
	gGraph(hashmapTop,graph);
	gGraph(hashmapBot,graph);
	return graph;
}
