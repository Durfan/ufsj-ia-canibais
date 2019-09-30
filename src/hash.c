#include "./includes/main.h"

State *initMap(void) {
	State *hashmap = malloc(MAPSIZE*sizeof(State));
	assert(hashmap);

	for (int i=0; i < MAPSIZE; i++) {
		hashmap[i].m = -1;
		hashmap[i].c = -1;
		hashmap[i].b = -1;
		hashmap[i].src = -1;
		hashmap[i].deep = -1;
		hashmap[i].dinner = false;
		hashmap[i].mapped = false;
	}

	return hashmap;
}

State setState(int m, int c) {
	State state;
	state.m = m;
	state.c = c;
	state.b = 1;
	state.src = hashKey(state);
	state.deep = 0;
	state.dinner = false;
	state.mapped = false;
	return state;
}

int hashKey(State state) {
	char buffer[0x004];
	sprintf(buffer, "%d%d", state.m*2,state.c);
	int hash = atoi(buffer);
	hash |= 0x010;
	hash %= 0x010;
	hash += 0x010 * state.b;
	return hash;
}

void addState(State state, State *hashmap) {
	int key = hashKey(state);
	hashmap[key].m = state.m;
	hashmap[key].c = state.c;
	hashmap[key].b = state.b;
	hashmap[key].src = state.src;
	hashmap[key].deep = state.deep;
	hashmap[key].mapped = true;
	hashmap[key].dinner = state.dinner;
}

bool mapped(State state, State *hashmap) {
	int key = hashKey(state);
	return hashmap[key].mapped;
}