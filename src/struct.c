#include "./includes/main.h"

State *initMap(void) {
	State *hashmap = malloc(mapSize()*sizeof(State));
	assert(hashmap);

	for (int i=0; i < mapSize(); i++) {
		hashmap[i].m = -1;
		hashmap[i].c = -1;
		hashmap[i].b = -1;
		hashmap[i].dinner = false;
		hashmap[i].mapped = false;
		hashmap[i].parent = NULL;
	} 

    return hashmap;
}

State setState(int m, int c) {
	State state;
	state.m = m;
	state.c = c;
	state.b = 1;
	state.dinner = false;
	state.mapped = false;
	state.parent = NULL;
	return state;
}

int mapSize(void) {
	static short int size;
	size = grabKey(M,C,B)+1;
	return size;
}

int hashKey(State state) {
	int m = state.m;
	int c = state.c;
	int b = state.b;
	return (m*10+c+100*b);
}

int grabKey(int m, int c, int b) {
	return (m*10+c+100*b);
}

void addState(State state, State *hashmap) {
	int key = hashKey(state);
	hashmap[key].m = state.m;
	hashmap[key].c = state.c;
	hashmap[key].b = state.b;
	hashmap[key].mapped = true;
	hashmap[key].dinner = state.dinner;
	hashmap[key].parent = state.parent;
}

bool mapped(State state, State *hashmap) {
	int key = hashKey(state);
	return hashmap[key].mapped;
}

void gGraph(State *hashmap, int **graph) {
	int parent;
	for (int i=0; i < mapSize(); i++) {
		if (hashmap[i].mapped && hashmap[i].parent != NULL) {
			parent = hashKey(*hashmap[i].parent);
			//graph[i][parent] = 1;
			graph[parent][i] = 1;
		}
		else if (hashmap[i].mapped && hashmap[i].parent == NULL)
			graph[i][i] = 1;
	}
}