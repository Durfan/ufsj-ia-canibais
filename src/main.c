#include "./includes/main.h"
  
int main(void) {

	State start = setState(M,C);
 	State *hashmap = initMap();

	addState(start,hashmap);
	expand(start,hashmap);


	for (int i=0; i < 10; i++) {
		for (int j=0; j <= mapSize(); j++) {
			if (!hashmap[j].dinner)
				expand(hashmap[j],hashmap);
		}
	}

 	for (int i=0; i <= mapSize(); i++) {
		if (hashmap[i].mapped && hashmap[i].parent != NULL) {
			printf(" %03d: (", i);
			switch (hashmap[i].b) {
			case 0:				
				printf("%d,", hashmap[i].m);
				printf("%d,", hashmap[i].c);
				printf("%d" , hashmap[i].parent->b);
				printf(") \u27A1 (");
				printf("%d,", M - hashmap[i].m);
				printf("%d,", C - hashmap[i].c);
				printf("%d" , hashmap[i].b);
				break;
			case 1:
				printf("%d,", M - hashmap[i].m);
				printf("%d,", C - hashmap[i].c);
				printf("%d" , hashmap[i].parent->b);
				printf(") \u27A1 (");
				printf("%d,", hashmap[i].m);
				printf("%d,", hashmap[i].c);
				printf("%d" , hashmap[i].b);
				break;
			
			default:
				exit(1);
				break;
			}
			printf (hashmap[i].dinner ? ") \u2620\n":")\n");
		}
	}

	return 0;
}