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

void largura(void) {
	State *hashmap = initMap();
	Deque *deque = dqcreate();
	int **graph = iniGraph();
	int visited = 0;

	State start = setState(M,C);
	addState(start,hashmap);

	dqpshHead(deque,hashKey(start));
	State visitado;

	while (!dqEmpty(deque)) {
		//dqprt(deque);
		visitado = hashmap[dqpopHead(deque)];
		expand(visitado,hashmap,deque,graph);
		visited++;
	}

	prtData("Largura",visited,hashmap,graph);

	genDot(hashmap,graph,"largura");
	genViz(hashmap,graph,"largura");

	dqclr(deque);
	delGraph(graph);
	free(hashmap);
}

void profund(void) {
	State *hashmap = initMap();
	Deque *deque = dqcreate();
	int **graph = iniGraph();
	int visited = 0;

	State start = setState(M,C);
	addState(start,hashmap);

	dqpshHead(deque,hashKey(start));
	State visitado;

	while (!dqEmpty(deque)) {
		//dqprt(deque);
		visitado = hashmap[dqpopTail(deque)];
		expand(visitado,hashmap,deque,graph);
		visited++;
	}

	prtData("Profundidade",visited,hashmap,graph);

	genDot(hashmap,graph,"profund");
	genViz(hashmap,graph,"profund");

	dqclr(deque);
	delGraph(graph);
	free(hashmap);
}

void prtData(char *busca, int visited, State *hashmap, int **graph) {
	printf("\n ---------------------------------------------\n");
	printf(" Busca: %s\n\n", busca);
	prtGraph(graph);
	printf("\n");
	prtMap(hashmap);
	printf("\n");
	printf(" Visitados: %02d\n", visited);
	printf("  Mapeados: %02d\n", stMapp(hashmap));
}

int stMapp(State *hashmap) {
	int mapped = 0;
	for (int i=0; i < MAPSIZE; i++) {
		if (hashmap[i].mapped)
			mapped++;
	}
	return mapped;
}