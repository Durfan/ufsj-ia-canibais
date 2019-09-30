#include "./includes/main.h"

void timeresult(clock_t start, char *file) {
    clock_t diff = clock() - start;
	double time = ((double)diff) / CLOCKS_PER_SEC;
    printf(" F Tempo: %fs\n", time);

	char output[0x100];
	strcpy(output,"./resources/graphs/");
	strcat(output,file);
	strcat(output,".js");
    FILE *fp = fopen(output,"a");
	if (fp == NULL) return;

	fprintf(fp,"\n$('span.tempo').text('%fs');",time);

	fclose(fp);
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