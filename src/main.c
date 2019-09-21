#include "./includes/main.h"

void prtState(State state, State *hashmap) {
	int key = hashKey(state);
	printf(" #%03x (", key);
	printf("%d,", hashmap[key].m);
	printf("%d,", hashmap[key].c);
	printf("%d" , hashmap[key].b);
	printf(") - (");
	printf("%d,", hashmap[key].parent->m);
	printf("%d,", hashmap[key].parent->c);
	printf("%d" , hashmap[key].parent->b);
	printf(")\n");
}
  
int main(void) {

	State start = setState(3,3);
 	State *hashmap = initMap(start);

	addState(start,hashmap);
	expand(start,hashmap);

/* 	for (int i=0; i <= 133; i++) {
		expand(hashmap[i],hashmap);
	} */

 	for (int i=0; i<=133; i++) {
		if (hashmap[i].mapped && hashmap[i].parent != NULL) {
			printf(" (");
			printf("%d,", hashmap[i].parent->m);
			printf("%d,", hashmap[i].parent->c);
			printf("%d" , hashmap[i].parent->b);
			printf(") \u27A1 (");
			printf("%d,", hashmap[i].m);
			printf("%d,", hashmap[i].c);
			printf("%d" , hashmap[i].b);
			printf (hashmap[i].dinner ? ") \u2620\n":")\n");
		}
	}

	return 0;
}