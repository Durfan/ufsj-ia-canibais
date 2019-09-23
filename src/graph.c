#include "./includes/main.h"

void genDot(State *hashmap, int **graph) {
	char *fpout = "./resources/graph.dot";
    FILE *fp = fopen(fpout,"w");
	assert(fp);

	State state;
	bool line;
	int m,c;

	fprintf(fp,"digraph {\n");
	for (int i=0; i < mapSize(); i++) {
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

	for (int i=0; i < mapSize(); i++) {
		line = false;
		for (int j=0; j < mapSize(); j++) {
			if (graph[i][j]) {
				switch (hashmap[i].b) {
				case 0:
					state = hashmap[i];
					m = hashmap[j].m - hashmap[i].m;
					c = hashmap[j].c - hashmap[i].c;
					break;
				case 1:
					state = hashmap[j];
					m = hashmap[i].m - hashmap[j].m;
					c = hashmap[i].c - hashmap[j].c;
					break;
				
				default:
					exit(1);
					break;
				}

				if (i != j) {
					fprintf(fp,"\t\"%d\" -> \"%d\"[label=\"%d,%d\", weight=\"%d,%d\"]\n", i,j,m,c,m,c);
				}
			}
		}
		if (line) printf("\n");
	}


	fprintf(fp,"}");

	fclose(fp);
}

