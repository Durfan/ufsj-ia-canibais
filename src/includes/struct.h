#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct state_t {
	int m,c,b;
	int src;
	bool mapped;
	bool dinner;
	struct state_t *parent;
} State;

State *initMap(void);
State setState(int m, int c);
int hashKey(State state);
void addState(State state, State *hashmap);
bool mapped(State state, State *hashmap);

#endif // _STRUCT_H