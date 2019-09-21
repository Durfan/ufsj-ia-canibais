#include "./includes/main.h"

void prtState(State state, State *hashmap) {
	int key = hashKey(state);
	printf(" #%03x (", key);
	printf("%d,", hashmap[key].m);
	printf("%d,", hashmap[key].c);
	printf("%d" , hashmap[key].b);
	printf(") - (");
	printf("%d,", hashmap[key].parent->m);
	printf("%d,", hashmap[key].parent->c);
	printf("%d" , hashmap[key].parent->b);
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
	State child;
	int parent = hashKey(state);
	
	int boat[][2] ={{2,0},{0,2},{1,1},{1,0},{0,1}};
	int carryM, carryC;

	for (int i=0; i<5; i++) {
		carryM = boat[i][0];
		carryC = boat[i][1];
		child = state;
		if (feasible(child,carryM,carryC)) {
			child.parent = &hashmap[parent];
			carry(&child,carryM,carryC);
			if (!lookup(child,hashmap)) {
				addState(child,hashmap);
			}
		}		
	}
}
  
int main(void) {

	State start = { M,C,1,NULL };
 	State *hashmap = initMap(start);

	printf("%d <---\n", hashKey(start)+1);

	addState(start,hashmap);
	expand(start,hashmap);

 	for (int i=0; i<=133; i++) {
		if (hashmap[i].m >= 0 && hashmap[i].parent != NULL) {
			printf(" (");
			printf("%d,", hashmap[i].m);
			printf("%d,", hashmap[i].c);
			printf("%d" , hashmap[i].b);
			printf(") - (");
			printf("%d,", hashmap[i].parent->m);
			printf("%d,", hashmap[i].parent->c);
			printf("%d" , hashmap[i].parent->b);
			printf(")\n");
		 }
	}

	

	return 0;
}