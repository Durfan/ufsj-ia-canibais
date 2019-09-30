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
	if (child.dinner) return;

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


void expand2(State state, State *hashmap, Deque *deque, int **graph) {

	State child = state;
	if (child.dinner) return;

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
				graph[hashKey(child)][child.src] = 1;
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

	State start = setState(M,C);
	addState(start,hashmap);

	dqpshHead(deque,hashKey(start));
	State visitado;

	while (!dqEmpty(deque)) {
		//dqprt(deque);
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


int buscaLimitada(int limit){
	State *hashmap = initMap();
	Deque *deque = dqcreate();
	int **graph = iniGraph();

	State start = setState(M,C);
	addState(start,hashmap);

	dqpshHead(deque,hashKey(start));
	State visitado;

	while (!dqEmpty(deque)) {
		//dqprt(deque);
		visitado = hashmap[dqpopTail(deque)];
		if(hashKey(visitado) == 0){
			genDot(hashmap,graph,"profund");
			genViz(hashmap,graph,"profund");
			genSol(hashmap,graph,"profund");
			printf("-------- \nBusca Iterativa:\n");
			prtGraph(graph);
			delGraph(graph);
			free(hashmap);
			return 1;
		}
		if(visitado.deep < limit){
			expand(visitado,hashmap,deque,graph);
		}

	}
	delGraph(graph);
	free(hashmap);
	return 0;
}

void buscaIterativa(void){
	int limit = 1;
	while(!buscaLimitada(limit)){
		limit++;
	}
}

void bidirecionalLargura(void){
	printf("\N------------------ Bidirecional");
	State *hashmapTop = initMap(), *hashmapBot = initMap();
	Deque *dequeTop = dqcreate();
	Deque *dequeBot = dqcreate();
	int **graph = iniGraph();
	State start = setState(M,C);
	State end; end.m = 0; end.c = 0; end.b = 0;

	dqpshHead(dequeTop,hashKey(start));
	dqpshHead(dequeBot, hashKey(end));

	addState(start,hashmapTop);
	addState(end, hashmapBot);

	int nodeTop = hashKey(start), nodeBot = hashKey(end);

	while(!dqEmpty(dequeTop) || !dqEmpty(dequeBot)){

		if(!dqEmpty(dequeTop)) nodeTop = dqpopHead(dequeTop);
		if(!dqEmpty(dequeBot)) nodeBot = dqpopHead(dequeBot);

		if(mapped(hashmapTop[nodeTop], hashmapBot)){
		//	unionHash(hashmapTop, hashmapBot);
			//genDot(hashmapTop,graph,"Bidirecional");
		//	genViz(hashmapTop,graph,"Bidirecional");
		//	genSol(hashmapTop,graph,"Bidirecional");
			prtGraph(graph);


			dqclr(dequeTop);
			dqclr(dequeBot);
			delGraph(graph);
			free(hashmapTop);
			free(hashmapBot);
		}
		expand2(hashmapBot[nodeBot], hashmapBot, dequeBot, graph);
		expand(hashmapTop[nodeTop], hashmapTop, dequeTop, graph);
	}
}

void profund(void) {
	State *hashmap = initMap();
	Deque *deque = dqcreate();
	int **graph = iniGraph();

	State start = setState(M,C);
	addState(start,hashmap);

	dqpshHead(deque,hashKey(start));
	State visitado;

	while (!dqEmpty(deque)) {
		//dqprt(deque);
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
