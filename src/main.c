#include "./includes/main.h"

typedef struct state_t {
	int m,c,b;
	struct state_t *parent;
} State;

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
}

void prtState(State state, State *hashmap) {
	int key = hashKey(state);
	printf(" #%03x (", key);
	printf("%d,", hashmap[key].m);
	printf("%d,", hashmap[key].c);
	printf("%d" , hashmap[key].b);
	printf(")\n");
}

bool lookup(State state, State *hashmap) {
	int key = hashKey(state);
	int m = hashmap[key].m;
	int c = hashmap[key].c;
	int b = hashmap[key].b;
	return (m+c+b > 0);
}

bool feasible(State state, int my, int cy) {
	bool feasible = false;
	int mx = state.m;
	int cx = state.c;

	if (state.b) {
		feasible = (my <= mx) && (cy <= cx);
	} else 
		feasible = (mx + my <= M) && (cx + cy <= C);

	return feasible;
}

void carry(State *state, int m, int c) {

	if (state->b) {
		state->m -= m;
		state->c -= c;
	} else {
		state->m += m;
		state->c += c;
	}
	state->b = !state->b;
}

void expand(State state, State *hashmap) {
	State newState;
	int key = hashKey(state);
	
	int boat[][2] ={{2,0},{0,2},{1,1},{1,0},{0,1}};
	int carryM, carryC;

	for (int i=0; i<5; i++) {
		carryM = boat[i][0];
		carryC = boat[i][1];
		newState = state;
		if (feasible(newState,carryM,carryC)) {
			carry(&newState,carryM,carryC);
			if (!lookup(newState,hashmap)) {
				newState.parent = &hashmap[key];
				addState(newState,hashmap);
			}
		}		
	}
}
  
int main(void) {

	State start = { M,C,1,NULL };

 	State *hashmap = malloc((hashKey(start)+1)*sizeof(State));
	memset(hashmap,-1,(hashKey(start)+1)*sizeof(State));

	addState(start,hashmap);

	for (int j = 0; j < 2; j++)
		for (int i=0; i<=133; i++) {
			if (hashmap[i].m != -1) {
				expand(hashmap[i],hashmap);
			}
		}

	for (int i=0; i<=133; i++) {
		if (hashmap[i].m >= 0) {
			printf(" #%03x (", i);
			printf("%d,", hashmap[i].m);
			printf("%d,", hashmap[i].c);
			printf("%d" , hashmap[i].b);
			printf(")\n");
		}
	}

	return 0;
}