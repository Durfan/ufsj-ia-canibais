#include "./includes/main.h"

int **iniGraph(void) {
	int **graph = calloc(MAPSIZE,sizeof(int*));
	assert(graph);
	for (int i=0; i < MAPSIZE; i++)
		graph[i] = calloc(MAPSIZE,sizeof(int));
	return graph;
}

void delGraph(int **graph) {
	for (int i=0 ; i < MAPSIZE ; i++)
		free(graph[i]);
	free(graph);
}

void prtGraph(int **graph) {
	bool line;
	for (int i=0; i < MAPSIZE; i++) {
		line = false;
		for (int j=0; j < MAPSIZE; j++) {
			if (graph[i][j]) {
				if (!line) {
					printf(" %d ->", i);
					line = true;
				}
				printf(" %d", j);
			}
		}
		if (line) printf("\n");
	}
}

void gGraph(State *hashmap, int **graph) {
	int parent;
	for (int i=0; i < MAPSIZE; i++) {
		if (hashmap[i].mapped && hashmap[i].src != -1) {
			parent = hashmap[i].src;
			graph[parent][i] = 1;
		}
	}
}

void genDot(State *hashmap, int **graph, char *file) {
	char output[0x100];
	strcpy(output,"./resources/graphs/");
	strcat(output,file);
	strcat(output,".dot");

	FILE *fp = fopen(output,"w");
	assert(fp);

	int m,c;

	fprintf(fp,"digraph {\n");
	for (int i=0; i < MAPSIZE; i++) {

		if (hashmap[i].mapped) {

			if (!hashmap[i].b) {
				m = M - hashmap[i].m;
				c = C - hashmap[i].c;
			}
			else {
				m = hashmap[i].m;
				c = hashmap[i].c;
			}

			fprintf(fp,"\t\"%d\"[label=",i);
			fprintf(fp,"\"(%d,%d,%d)\"",m,c,hashmap[i].b);

			if (hashmap[i].dinner)
				fprintf(fp,",style=filled,fillcolor=red]\n");
			else
				fprintf(fp,"]\n");
		}
	}

	for (int i=0; i < MAPSIZE; i++) {
		for (int j=0; j < MAPSIZE; j++) {

			if (graph[i][j]) {

				if (!hashmap[i].b) {
					m = hashmap[j].m - hashmap[i].m;
					c = hashmap[j].c - hashmap[i].c;
				}
				else {
					m = hashmap[i].m - hashmap[j].m;
					c = hashmap[i].c - hashmap[j].c;
				}

				if (i != j) {
					fprintf(fp,"\t\"%d\" -> \"%d\"",i,j);
					fprintf(fp,"[label=\"%d,%d\",",m,c);
					fprintf(fp,"weight=\"%d,%d\"]\n",m,c);
				}
			}
		}
	}

	fprintf(fp,"}");
	fclose(fp);
}

void genViz(State *hashmap, int **graph, char *file) {
	char output[0x100];
	strcpy(output,"./resources/graphs/");
	strcat(output,file);
	strcat(output,".js");

	FILE *fp = fopen(output,"w");
	assert(fp);

	int m,c;

	fprintf(fp,"const gData = {\n");
	fprintf(fp,"\tnodes: [\n");
	for (int i=MAPSIZE-1; i >= 0; i--) {

		if (hashmap[i].mapped) {

			if (!hashmap[i].b) {
				m = M - hashmap[i].m;
				c = C - hashmap[i].c;
			}
			else {
				m = hashmap[i].m;
				c = hashmap[i].c;
			}

			fprintf(fp,"\t{ id: %d, name: \"(",i);
			fprintf(fp,"%d,%d,%d)\"",m,c,hashmap[i].b);
			//fprintf(fp,", val: %d", hashmap[i].deep);

			if (hashmap[i].m == 0 && hashmap[i].c == 0)
				fprintf(fp,", color: \"green\" },\n");
			else if (hashmap[i].m == M && hashmap[i].c == C)
				fprintf(fp,", color: \"green\" },\n");
			else if (hashmap[i].dinner)
				fprintf(fp,", color: \"red\" },\n");
			else
				fprintf(fp," },\n");
		}
	}

	fprintf(fp,"\t],\n\tlinks: [\n");

	for (int i=0; i < MAPSIZE; i++) {
		for (int j=0; j < MAPSIZE; j++) {

			if (graph[i][j]) {

				if (!hashmap[i].b) {
					m = hashmap[j].m - hashmap[i].m;
					c = hashmap[j].c - hashmap[i].c;
				}
				else {
					m = hashmap[i].m - hashmap[j].m;
					c = hashmap[i].c - hashmap[j].c;
				}

				if (i != j) {
					fprintf(fp,"\t{ target: %d, source: %d,",j,i);
					fprintf(fp," name: \"%d,%d\" },\n",m,c);
				}
			}
		}
	}
	
	fprintf(fp,"\t]\n};");
	fclose(fp);
}