#define SMALLER(X, Y) ((X) > (Y) ? (Y) : (X))
#define MIN(X, Y, Z) SMALLER(X, SMALLER(Y, Z))

void genStates(List *in, List *out);
void expand(List *in, List *out);
void feasible(State *state, bool *rules);
void carry(State *state, int rule);
bool valid(State *state, int m, int c);
bool isLegal(State state);

void genStates(List *in, List *out) {

	int count = 0;
	while (count < 10) {
		expand(in,out);
		llpop(in);
		count++;
	}	
}

void expand(List *in, List *out) {
	
	llpsh(out,in->head->state);
	State state = in->head->state;
	State *parent = &out->head->state;
	State newState;

	for (int m=1; m <= SMALLER(state.m, 2); m++) {
		for (int c=0; c <= MIN(m, state.c, 2 - m); c++) {
			newState = state;
			newState.m -= m;
			newState.c -=c;
			newState.b = !newState.b;
			newState.parent = parent;
			if (isLegal(newState))
				llins(in,newState);
		}
	}

	for (int c=1; c <= SMALLER(state.c, 2); c++) {
		newState = state;
		newState.c -= c;
		newState.b = !newState.b;
		newState.parent = parent;
		if (isLegal(newState))
			llins(in,newState);
	}
}

bool isLegal(State state) {
	if ((state.m != 0) && (state.m != 3)) {
		if (state.m == state.c)
			return true;
		else
			return false;
	}
	else
		return true;
}

void feasible(State *state, bool *rules) {
	int carry[5][2] = { {2,0}, {0,2}, {1,1}, {1,0}, {0,1} };
	int m,c;
	int m1 = state->m;
	int c1 = state->c;

	for (int i=0; i<5; i++) {
		m = carry[i][0];
		c = carry[i][1];
		switch (state->b) {
		case 0:
			rules[i] = rules[i] && ((m + m1 <= 3) && (c + c1 <= 3));
			break;
		case 1:
			rules[i] = rules[i] && ((m <= m1) && (c <= c1));
			break;
		
		default:
			break;
		}
	}
}