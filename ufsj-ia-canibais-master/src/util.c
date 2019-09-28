#include "./includes/main.h"

void prtMap(State *hashmap) {

	for (int i=0; i < MAPSIZE; i++) {
		if (hashmap[i].mapped && hashmap[i].parent != NULL) {
			printf(" %03d: (", i);
			switch (hashmap[i].b) {
			case 0:				
				printf("%d,", hashmap[i].m);
				printf("%d,", hashmap[i].c);
				printf("%d" , hashmap[i].parent->b);
				printf(") \u27A1 ");
				printf("[%d,", hashmap[i].parent->m - hashmap[i].m);
				printf("%d] ", hashmap[i].parent->c - hashmap[i].c);
				printf("\u27A1 (");
				printf("%d,", M - hashmap[i].m);
				printf("%d,", C - hashmap[i].c);
				printf("%d" , hashmap[i].b);
				printf(") : [%d]", hashmap[i].src);
				break;
			case 1:
				printf("%d,", M - hashmap[i].m);
				printf("%d,", C - hashmap[i].c);
				printf("%d" , hashmap[i].parent->b);
				printf(") \u27A1 ");
				printf("[%d,", hashmap[i].m - hashmap[i].parent->m);
				printf("%d] ", hashmap[i].c - hashmap[i].parent->c);
				printf("\u27A1 (");
				printf("%d,", hashmap[i].m);
				printf("%d,", hashmap[i].c);
				printf("%d" , hashmap[i].b);
				printf(") : [%d]", hashmap[i].src);
				break;
			
			default:
				exit(1);
				break;
			}
			printf (hashmap[i].dinner ? " \u2620\n":"\n");
		}
	}

}