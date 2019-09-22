#include "./includes/main.h"
  
int main(void) {

	State start = setState(M,C);
 	State *hashmap = initMap();

	addState(start,hashmap);
	expand(start,hashmap);


	for (int i=0; i < 10; i++) {
		for (int j=0; j < mapSize(); j++) {
			if (!hashmap[j].dinner)
				expand(hashmap[j],hashmap);
		}
	}

	prtMap(hashmap);

	free(hashmap);
	return 0;
}