#include "./includes/main.h"

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

void isDinner(State *state) {
	int mx = state->m;
	int cx = state->c;
	int my = state->parent->m - state->m;
	int cy = state->parent->c - state->c;
	bool dinner  = (cx > mx) && (mx != 0);
	bool dessert = (cy > my) && (my != 0);
	state->dinner = dinner || dessert;
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
	int m,c;

	for (int i=0; i < 5; i++) {
		m = boat[i][0];
		c = boat[i][1];
		child = state;
		if (feasible(child,m,c)) {
			child.parent = &hashmap[parent];
			carry(&child,m,c);
			isDinner(&child);
			if (!mapped(child,hashmap))
				addState(child,hashmap);
		}		
	}
}