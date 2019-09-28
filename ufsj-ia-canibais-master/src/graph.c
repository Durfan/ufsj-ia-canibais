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
		if (hashmap[i].mapped && hashmap[i].parent != NULL) {
			parent = hashKey(*hashmap[i].parent);
			//graph[i][parent] = 1;
			graph[parent][i] = 1;
		}
		else if (hashmap[i].mapped && hashmap[i].parent == NULL)
			graph[i][i] = 1;
	}
}

void genDot(State *hashmap, int **graph) {
	char *fpout = "./resources/graph.dot";
    FILE *fp = fopen(fpout,"w");
	assert(fp);

	bool line;
	int m,c;

	fprintf(fp,"digraph {\n");
	for (int i=0; i < MAPSIZE; i++) {
		if (hashmap[i].mapped) {
			switch (hashmap[i].b) {
			case 0:
				fprintf(fp,"\t\"%d\"[label=\"(", i);
				fprintf(fp,"%d,", M - hashmap[i].m);
				fprintf(fp,"%d,", C - hashmap[i].c);
				fprintf(fp,"%d)", hashmap[i].b);
				fprintf(fp,"\"]\n");
				break;
			case 1:
				fprintf(fp,"\t\"%d\"[label=\"(", i);
				fprintf(fp,"%d,", hashmap[i].m);
				fprintf(fp,"%d,", hashmap[i].c);
				fprintf(fp,"%d)", hashmap[i].b);
				fprintf(fp,"\"]\n");
				break;
			
			default:
				break;
			}
		}
		if (hashmap[i].dinner)
			fprintf(fp,"\t\"%d\"[style=filled,fillcolor=red]\n", i);
	}

	for (int i=0; i < MAPSIZE; i++) {
		line = false;
		for (int j=0; j < MAPSIZE; j++) {
			if (graph[i][j]) {
				switch (hashmap[i].b) {
				case 0:
					m = hashmap[j].m - hashmap[i].m;
					c = hashmap[j].c - hashmap[i].c;
					break;
				case 1:
					m = hashmap[i].m - hashmap[j].m;
					c = hashmap[i].c - hashmap[j].c;
					break;
				
				default:
					exit(1);
					break;
				}

				if (i != j) {
					fprintf(fp,"\t\"%d\" -> \"%d\"", i,j);
					fprintf(fp,"[label=\"%d,%d\",", m,c);
					fprintf(fp," weight=\"%d,%d\"]\n", m,c);
				}
			}
		}
		if (line) printf("\n");
	}


	fprintf(fp,"}");

	fclose(fp);
}

void genViz(State *hashmap, int **graph) {
	char *fpout = "./resources/graph.js";
    FILE *fp = fopen(fpout,"w");
	assert(fp);

	bool line;
	int m,c;

	fprintf(fp,"const gData = {\n");
	fprintf(fp,"\tnodes: [\n");
	for (int i=MAPSIZE; i >= 0; i--) {
		if (hashmap[i].mapped) {
			switch (hashmap[i].b) {
			case 0:
				if (hashmap[i].m == 0 && hashmap[i].c == 0) {
					fprintf(fp,"\t{ id: %d, name: \"(", i);
					fprintf(fp,"%d,", hashmap[i].m);
					fprintf(fp,"%d,", hashmap[i].c);
					fprintf(fp,"%d)", hashmap[i].b);
					fprintf(fp,"\", color: \"green\" },\n");
				}
				else {
					fprintf(fp,"\t{ id: %d, name: \"(", i);
					fprintf(fp,"%d,", M - hashmap[i].m);
					fprintf(fp,"%d,", C - hashmap[i].c);
					fprintf(fp,"%d)", hashmap[i].b);
					if (hashmap[i].dinner)
						fprintf(fp,"\", color: \"red\" },\n");
					else
						fprintf(fp,"\" },\n");
				}
				break;
			case 1:
				if (hashmap[i].m == M && hashmap[i].c == C) {
					fprintf(fp,"\t{ id: %d, name: \"(", i);
					fprintf(fp,"%d,", hashmap[i].m);
					fprintf(fp,"%d,", hashmap[i].c);
					fprintf(fp,"%d)", hashmap[i].b);
					fprintf(fp,"\", color: \"green\" },\n");
				}
				else {
					fprintf(fp,"\t{ id: %d, name: \"(", i);
					fprintf(fp,"%d,", hashmap[i].m);
					fprintf(fp,"%d,", hashmap[i].c);
					fprintf(fp,"%d)", hashmap[i].b);
					if (hashmap[i].dinner)
						fprintf(fp,"\", color: \"red\" },\n");
					else
						fprintf(fp,"\" },\n");
				}
				break;
			
			default:
				break;
			}
		}
	}

	fprintf(fp,"\t],\n\tlinks: [\n");

	for (int i=0; i < MAPSIZE; i++) {
		line = false;
		for (int j=0; j < MAPSIZE; j++) {
			if (graph[i][j]) {
				switch (hashmap[i].b) {
				case 0:
					m = hashmap[j].m - hashmap[i].m;
					c = hashmap[j].c - hashmap[i].c;
					break;
				case 1:
					m = hashmap[i].m - hashmap[j].m;
					c = hashmap[i].c - hashmap[j].c;
					break;
				
				default:
					exit(1);
					break;
				}

				if (i != j) {
					fprintf(fp,"\t{ target: %d, source: %d,", j,i);
					fprintf(fp," name: \"%d,%d\" },\n", m,c);
				}
			}
		}
		if (line) printf("\n");
	}

	fprintf(fp,"\t]\n};");

	fclose(fp);
}