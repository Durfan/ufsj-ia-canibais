#include "./includes/main.h"

int expandAndStack(State state, State *hashmap, Stack *stack) {
	State child;
	int m,c,parent = hashKey(state);
	int boat[][2] ={{2,0},{0,2},{1,1},{1,0},{0,1}};
	int flag = 0;

	for (int i=0; i < 5; i++) {
		m = boat[i][0];
		c = boat[i][1];
		child = state;
		child.parent = &hashmap[parent];
		if (feasible(child,m,c)) {
			carry(child,m,c);
			child = isDinner(child);
			if (!mapped(child,hashmap) && !child.dinner){
			   flag = 1;
			   addState(child,hashmap);
		       pop(stack, hashKey(child));
            }
		}
	}

	return flag;
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


int **depthSearch(State start, State *hashmap){
    Stack *stack = initStack();

	// Search
    addState(start, hashmap);
    expandAndStack(start, hashmap, stack);

    int actualNode;
	int **graph = iniGraph();
	
	while (!stackIsEmpty(stack)) {
        actualNode = push(stack);
        if (hashmap[actualNode].m == 0 && hashmap[actualNode].c == 0){
			constructionSolution(start, actualNode, hashmap, graph);
			destroyStack(stack);
			return graph;
       }
	   else {
			expandAndStack(hashmap[actualNode], hashmap, stack);
		}
    }

	return graph;
}
