#include "./includes/main.h"

void prtFOOclk(struct timeval tv1, struct timeval tv2) {
    printf("   F Tempo: %fs\n", ftempo(tv1,tv2));
}

// Calcula o tempo de execucao até determinado ponto
double ftempo(struct timeval tv1, struct timeval tv2) {
    return (double)(tv2.tv_usec - tv1.tv_usec)/1000000 +
           (double)(tv2.tv_sec-tv1.tv_sec);
}

void prtMap(State *hashmap) {
	int src;
	State parent;

	for (int i=0; i < MAPSIZE; i++) {
		if (hashmap[i].mapped) {
			src = hashmap[i].src;
			parent = hashmap[src];
			printf(" %03d: (", i);
			switch (hashmap[i].b) {
			case 0:				
				printf("%d,", hashmap[i].m);
				printf("%d,", hashmap[i].c);
				printf("%d" , parent.b);
				printf(") \u27A1 ");
				printf("[%d,", parent.m - hashmap[i].m);
				printf("%d] ", parent.c - hashmap[i].c);
				printf("\u27A1 (");
				printf("%d,", M - hashmap[i].m);
				printf("%d,", C - hashmap[i].c);
				printf("%d" , hashmap[i].b);
				break;
			case 1:
				printf("%d,", M - hashmap[i].m);
				printf("%d,", C - hashmap[i].c);
				printf("%d" , parent.b);
				printf(") \u27A1 ");
				printf("[%d,", hashmap[i].m - parent.m);
				printf("%d] ", hashmap[i].c - parent.c);
				printf("\u27A1 (");
				printf("%d,", hashmap[i].m);
				printf("%d,", hashmap[i].c);
				printf("%d" , hashmap[i].b);
				break;
			
			default:
				exit(1);
				break;
			}
			printf(") : deep %02d : src[%02d]", hashmap[i].deep, hashmap[i].src);
			printf (hashmap[i].dinner ? " \u2620\n":"\n");
		}
	}

}