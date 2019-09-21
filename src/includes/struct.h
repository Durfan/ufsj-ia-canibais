#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct state_t {
	int m,c,b;
	struct state_t *parent;
} State;

State *initMap(State start);
int hashKey(State state);
void addState(State state, State *hashmap);

#endif // _STRUCT_H