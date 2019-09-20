#include "./includes/main.h"

void genStates(List *in, List *out);
void expand(List *in, List *out);
void carry(State *state, int m, int c);
bool isDinner(State state);
bool loop(State *state);
bool feasible(State *state, int my, int cy);
  
int main(void) {

	List *in  = create();
	List *out = create();

	State state0 = { M,C,1,false,NULL };
	llpshHead(in,state0);

	genStates(in,out);
	out->done = true;

	llprt(in);
	llprt(out);

	llclr(in);
	llclr(out);

	return 0;
}

void genStates(List *in, List *out) {

	int count = 0;
	while (count < 2) {
		expand(in,out);
		llpopHead(in);
		count++;
	}	
}

void expand(List *in, List *out) {
	llpshHead(out,in->head->state);
	State state = in->head->state;
	State newState, *parent = &out->head->state;
	
	int boat[][2] ={{2,0},{0,2},{1,1},{1,0},{0,1}};
	int carryM, carryC;

	for (int i=0; i<5; i++) {
		carryM = boat[i][0];
		carryC = boat[i][1];
		newState = state;
		newState.parent = parent;
		if (feasible(&newState,carryM,carryC)) {
			carry(&newState,carryM,carryC);
			newState.dinner = isDinner(newState);
			llpshTail(out,newState);
			if (!newState.dinner)
				llpshTail(in,newState);
		}		
	}
}

void carry(State *state, int m, int c) {

	if (state->b) {
		state->m -= m;
		state->c -= c;
	} else {
		state->m += m;
		state->c += c;
	}

	state->dinner = false;
	state->b = !state->b;
}

bool isDinner(State state) {
	int mx = state.m;
	int cx = state.c;
	int my = state.parent->m - state.m;
	int cy = state.parent->c - state.c;
	bool dinner  = (cx > mx) && (mx != 0);
	bool dessert = (cy > my) && (my != 0);
	return (dinner || dessert);
}

bool feasible(State *state, int my, int cy) {
	bool feasible = false;
	int mx = state->m;
	int cx = state->c;

	switch (state->b) {
	case 0:
		feasible = (mx + my <= M) && (cx + cy <= C);
		break;
	case 1:
		feasible = (my <= mx) && (cy <= cx);
		break;
	
	default:
		exit(1);
		break;
	}

	return feasible;
}

bool loop(State *state) {
	bool lm = state->m == state->parent->m;
	bool lc = state->c == state->parent->c;
	return (lm && lc);
}