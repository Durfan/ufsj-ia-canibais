#include "./includes/main.h"

int main(void) {

	State start = setState(M,C);
 	State *hashmap = initMap();
	int stMppd,hSize;

	hSize = mapSize();
	addState(start,hashmap);
	expand(start,hashmap);

 	for (int i=0; i < 10; i++) {
		for (int j=0; j < hSize; j++) {
			expand(hashmap[j],hashmap);
		}
	}

	prtMap(hashmap);

	stMppd = stMapp(hashmap);
	printf("\n Estados Mapeados: %d\n\n", stMppd);

	int **graph = iniArray(hSize,hSize);
	gGraph(hashmap,graph);
	pGraph(graph,hSize);

	delArray(graph,hSize);
	free(hashmap);
	return 0;
}