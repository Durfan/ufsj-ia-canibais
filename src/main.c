#include "./includes/main.h"
  
int main(void) {

	State start = setState(3,3);
 	State *hashmap = initMap();

	addState(start,hashmap);
	expand(start,hashmap);

	for (int i=0; i <= mapSize(); i++) {
		expand(hashmap[i],hashmap);
	}

 	for (int i=0; i <= mapSize(); i++) {
		if (hashmap[i].mapped && hashmap[i].parent != NULL) {
			switch (hashmap[i].b) {
			case 0:
				printf(" (");
				printf("%d,", hashmap[i].parent->m);
				printf("%d,", hashmap[i].parent->c);
				printf("%d" , hashmap[i].parent->b);
				printf(") \u27A1 ");
				printf("[%d,%d]", hashmap[i].parent->m - hashmap[i].m, hashmap[i].parent->c - hashmap[i].c);
				printf(" \u27A1 (");
				printf("%d,", M - hashmap[i].m);
				printf("%d,", C - hashmap[i].c);
				printf("%d" , hashmap[i].b);
				printf (hashmap[i].dinner ? ") \u2620\n":")\n");
				break;
			case 1:
				printf(" (");
				printf("%d,", M - hashmap[i].parent->m);
				printf("%d,", C - hashmap[i].parent->c);
				printf("%d" , hashmap[i].parent->b);
				printf(") \u27A1 (");
				printf("%d,", M - hashmap[i].m);
				printf("%d,", C - hashmap[i].c);
				printf("%d" , hashmap[i].b);
				printf (hashmap[i].dinner ? ") \u2620\n":")\n");
				break;
			
			default:
				exit(1);
				break;
			}
		}
	}

	return 0;
}