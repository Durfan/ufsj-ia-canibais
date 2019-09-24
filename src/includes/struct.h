#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct state_t {
	int m,c,b;
	bool mapped;
	bool dinner;
	struct state_t *parent;
} State;

State *initMap(void);
State setState(int m, int c);
int mapSize(void);
int hashKey(State state);
int grabKey(int m, int c, int b);
void addState(State state, State *hashmap);
bool mapped(State state, State *hashmap);

#endif // _STRUCT_H