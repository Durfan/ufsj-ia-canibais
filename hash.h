#ifndef _HASH_H
#define _HASH_H

typedef struct state_t {
	int m,c,b;
	int src;
	int deep;
	bool mapped;
	bool dinner;
} State;

State *initMap(void);
State setState(int m, int c);
int hashKey(State state);
void addState(State state, State *hashmap);
bool mapped(State state, State *hashmap);
void unionHash(State *hashmapOri, State *hasmhapDest);
#endif // _HASH_H
