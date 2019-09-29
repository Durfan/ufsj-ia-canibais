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

void expand(State state, State *hashmap, Deque *deque, int **graph) {

	State child = state;
	if (child.dinner || !hashKey(state)) return;

	int m,c,boat[][2] = { {2,0},{0,2},{1,1},{1,0},{0,1} };

	for (int i=0; i < 5; i++) {
		m = boat[i][0];
		c = boat[i][1];
		child = state;
		child.deep++;
		if (feasible(child,m,c)) {
			child = carry(child,m,c);
			child.src = hashKey(state);
			child = isDinner(child);
			if (!mapped(child,hashmap)) {
				graph[child.src][hashKey(child)] = 1;
				addState(child,hashmap);
				dqpshTail(deque,hashKey(child));
			}
		}
	}
}

void largura(State state, State *hashmap) {
	Deque *deque = dqcreate();
	int **graph = iniGraph();

	addState(state,hashmap);
	dqpshHead(deque,hashKey(state));
	State visitado;

	while (!dqEmpty(deque)) {
		//dqprt(deque);
		visitado = hashmap[dqpopHead(deque)];
		expand(visitado,hashmap,deque,graph);
		metrica(true);
	}

	printf(" Visitados -> %02d\n", metrica(false));

	prtGraph(graph);
	genDot(hashmap,graph);
	genViz(hashmap,graph);

	dqclr(deque);
	delGraph(graph);
}

void profund(State state, State *hashmap) {
	Deque *deque = dqcreate();
	int **graph = iniGraph();

	addState(state,hashmap);
	dqpshHead(deque,hashKey(state));
	State visitado;

	while (!dqEmpty(deque)) {
		//dqprt(deque);
		visitado = hashmap[dqpopTail(deque)];
		expand(visitado,hashmap,deque,graph);
		metrica(true);
	}

	printf(" Visitados -> %02d\n", metrica(false));

	prtGraph(graph);
	genDot(hashmap,graph);
	genViz(hashmap,graph);

	dqclr(deque);
	delGraph(graph);
}

int metrica(bool count) {
	static int visited;
	if (count)
		visited++;
	return visited;
}

int stMapp(State *hashmap) {
	int mapped = 0;
	for (int i=0; i < MAPSIZE; i++) {
		if (hashmap[i].mapped)
			mapped++;
	}
	return mapped;
}