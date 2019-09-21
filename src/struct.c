#include "./includes/main.h"

State *initMap(State start) {
	unsigned short mapSize = hashKey(start)+1;
	State *hashmap = malloc(mapSize*sizeof(State));
	assert(hashmap);

	for (int i=0; i < mapSize; i++) {
		hashmap[i].m = -1;
		hashmap[i].c = -1;
		hashmap[i].b = -1;
		hashmap[i].parent = NULL;
	} 

    return hashmap;
}

int hashKey(State state) {
	int m = state.m;
	int c = state.c;
	int b = state.b;
	return (m*10+c+100*b);
}

void addState(State state, State *hashmap) {
	int key = hashKey(state);
	hashmap[key].m = state.m;
	hashmap[key].c = state.c;
	hashmap[key].b = state.b;
	hashmap[key].parent = state.parent;
}