#include "./includes/main.h"

State carry(State state, int m, int c) {

	if (state.b) {
		state.m -= m;
		state.c -= c;
	} else {
		state.m += m;
		state.c += c;
	}
	state.b = !state.b;

	return state;
}

bool feasible(State state, int m, int c) {

	if (state.b)
		return (state.m >= m) && (state.c >= c);
	return (M - state.m >= m) && (C - state.c >= c);
}

State isDinner(State state) {
	int mx,cx,my,cy;

	if (state.b) {
		mx = state.m;
		cx = state.c;
		my = M - state.m;
		cy = C - state.c;
	}
	else {
		mx = M - state.m;
		cx = C - state.c;
		my = state.m;
		cy = state.c;
	}

	bool dinner  = (cx > mx) && (mx != 0);
	bool dessert = (cy > my) && (my != 0);
	state.dinner = dinner || dessert;

	return state;
}

void expand(State state, State *hashmap) {
	State child;
	int m,c,parent = hashKey(state);
	int boat[][2] ={{2,0},{0,2},{1,1},{1,0},{0,1}};

	for (int i=0; i < 5; i++) {
		m = boat[i][0];
		c = boat[i][1];
		child = state;
		child.parent = &hashmap[parent];
		if (feasible(child,m,c)) {
			child = carry(child,m,c);
			child = isDinner(child);
			if (!mapped(child,hashmap))
				addState(child,hashmap);
		}		
	}
}

int stMapp(State *hashmap) {
	int mapped = 0;
	for (int i=0; i < mapSize(); i++) {
		if (hashmap[i].mapped)
			mapped++;
	}
	return mapped;
}

void gGraph(State *hashmap, int **array) {
	int parent;
	for (int i=0; i < mapSize(); i++) {
		if (hashmap[i].mapped && hashmap[i].parent != NULL) {
			parent = hashKey(*hashmap[i].parent);
			array[i][parent] = 1;
			array[parent][i] = 1;
		}
	}
}

void pGraph(int **array, int size) {
	bool line = false;

	for (int i=0; i < size; i++) {
		line = false;
		
		for (int j=0; j < size; j++) {
			if (array[i][j]) {
				if (!line) {
					printf(" %d ->", i);
					line = true;
				}
				printf(" %d", j);
			}
		}
		if (line)
			printf("\n");
	}
}