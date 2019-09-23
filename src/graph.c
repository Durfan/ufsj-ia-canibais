#include "./includes/main.h"

void genDot(State *hashmap, int **graph) {
	char *fpout = "./resources/graph.dot";
    FILE *fp = fopen(fpout,"w");
	assert(fp);

	//State state0, state1;
	bool line;

	fprintf(fp,"digraph {\n");
	for (int i=0; i < mapSize(); i++) {
		if (hashmap[i].dinner)
			fprintf(fp,"\t\"%d\"[style=filled,fillcolor=red]\n", i);
	}

	for (int i=0; i < mapSize(); i++) {
		line = false;
		for (int j=0; j < mapSize(); j++) {
			if (graph[i][j]) {
				//state1 = hashmap[i];
				//state0 = hashmap[j];
				if (i != j)
					fprintf(fp,"\t\"%d\" -> \"%d\"\n", i,j);
			}
		}
		if (line) printf("\n");
	}


	fprintf(fp,"}");

	fclose(fp);
}

