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
	if (child.dinner || child.deep > 10)
		return;

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

	State start = setState(M,C,1);
	addState(start,hashmap);

	dqpshHead(deque,hashKey(start));
	State visitado;

	while (!dqEmpty(deque)) {
		visitado = hashmap[dqpopHead(deque)];
		expand(visitado,hashmap,deque,graph);
	}

	genDot(hashmap,graph,"largura");
	genViz(hashmap,graph,"largura");
	genSol(hashmap,graph,"largura");

	dqclr(deque);
	delGraph(graph);
	free(hashmap);
}

void profund(void) {
	State *hashmap = initMap();
	Deque *deque = dqcreate();
	int **graph = iniGraph();

	State start = setState(M,C,1);
	addState(start,hashmap);

	dqpshHead(deque,hashKey(start));
	State visitado;

	while (!dqEmpty(deque)) {
		visitado = hashmap[dqpopTail(deque)];
		expand(visitado,hashmap,deque,graph);
	}

	genDot(hashmap,graph,"profund");
	genViz(hashmap,graph,"profund");
	genSol(hashmap,graph,"profund");

	dqclr(deque);
	delGraph(graph);
	free(hashmap);
}

void bidirec(void) {
	State *hashmap = initMap();
	Deque *deque = dqcreate();
	int **graph = iniGraph();

	State start = setState(M,C,1);
	State end   = setState(0,0,0);
	addState(start,hashmap);
	addState(end,hashmap);

	dqpshHead(deque,hashKey(start));
	dqpshTail(deque,hashKey(end));

	int bot,top,nt,nb;

	while (!dqEmpty(deque)) {

		if (deque->tail) {
			bot = dqpopTail(deque);
			expand(hashmap[bot],hashmap,deque,graph);
			if (!hashmap[bot].dinner) nb = bot;
		}

		if (deque->head) {
			top = dqpopHead(deque);
			expand(hashmap[top],hashmap,deque,graph);
			if (!hashmap[top].dinner) nt = top;
		}

	}

	graph[nt][nb] = 1;

	genDot(hashmap,graph,"bidirec");
	genViz(hashmap,graph,"bidirec");
	genSol(hashmap,graph,"bidirec");

	dqclr(deque);
	delGraph(graph);
	free(hashmap);
}

void iteratv(void) {
	int limit = 1;
	while (!limitada(limit))
		limit++;
}

int limitada(int limit) {
	State *hashmap = initMap();
	Deque *deque = dqcreate();
	int **graph = iniGraph();

	State start = setState(M,C,1);
	State visitado;
	addState(start,hashmap);

	dqpshHead(deque,hashKey(start));

	while (!dqEmpty(deque)) {
		
		visitado = hashmap[dqpopTail(deque)];
		
		if (hashKey(visitado) == 0) {

			genDot(hashmap,graph,"iteratv");
			genViz(hashmap,graph,"iteratv");
			genSol(hashmap,graph,"iteratv");

			dqclr(deque);
			delGraph(graph);
			free(hashmap);

			return 1;
		}

		if (visitado.deep < limit)
			expand(visitado,hashmap,deque,graph);

	}

	dqclr(deque);
	delGraph(graph);
	free(hashmap);

	return 0;
}

void genSol(State *hashmap, int **graph, char *file) {
	int memoria = stMapp(hashmap);

	printf("\n ---------------------------------------------\n");
	printf(" Busca: %s\n\n", file);
	prtGraph(graph);
	printf("\n");
	prtMap(hashmap);
	printf("\n");
	printf(" Memoria: %02d\n", memoria);

	char output[0x100];
	strcpy(output,"./resources/graphs/");
	strcat(output,file);
	strcat(output,".js");
	FILE *fp = fopen(output,"a");
	if (fp == NULL) return;

	fprintf(fp,"\n\n$('span.memoria').text('%d');\n", memoria);

	fclose(fp);
}

int stMapp(State *hashmap) {
	int mapped = 0;
	for (int i=0; i < MAPSIZE; i++) {
		if (hashmap[i].mapped)
			mapped++;
	}
	return mapped;
}