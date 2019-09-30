#include "./includes/main.h"

int **iniArray(int n, int m) {
    int **array = calloc(n,sizeof(int*));
	assert(array);
    for (int i=0; i < n; i++)
		array[i] = calloc(m,sizeof(int));
    return array;
}

void delArray(int **array, int n) {
    for (int i=0 ; i < n ; i++)
		free(array[i]);
    free(array);
}

void prtMap(State *hashmap) {

	for (int i=0; i < mapSize(); i++) {
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
				break;
			
			default:
				exit(1);
				break;
			}
			printf (hashmap[i].dinner ? ") \u2620\n":")\n");
		}
	}

}

char *stateInfo(State state, State *hashmap) {
	int key = hashKey(state);
	static char text[1024];
	static char buffer[1024];
	static char *pnull = "Nope";

	if (hashmap[key].parent == NULL)
		return pnull;

	if (!hashmap[key].b) {
		strcpy(text,"(");
		sprintf(buffer,"%d",hashmap[key].m);
		strcat(text,buffer);
		strcat(text,",");
		sprintf(buffer,"%d",hashmap[key].c);
		strcat(text,buffer);
		strcat(text,",");
		sprintf(buffer,"%d",hashmap[key].parent->b);
		strcat(text,buffer);
		strcat(text,") ");
	
		strcat(text,"[");
		sprintf(buffer,"%d",hashmap[key].parent->m - hashmap[key].m);
		strcat(text,buffer);
		strcat(text,",");
		sprintf(buffer,"%d",hashmap[key].parent->c - hashmap[key].c);
		strcat(text,buffer);
		strcat(text,"]");

		strcat(text," (");
		sprintf(buffer,"%d", M - hashmap[key].m);
		strcat(text,buffer);
		strcat(text,",");
		sprintf(buffer,"%d", C - hashmap[key].c);
		strcat(text,buffer);
		strcat(text,",");
		sprintf(buffer,"%d",hashmap[key].b);
		strcat(text,buffer);
		strcat(text,")");
	}
	else {
		strcpy(text,"(");
		sprintf(buffer,"%d", M - hashmap[key].m);
		strcat(text,buffer);
		strcat(text,",");
		sprintf(buffer,"%d", C - hashmap[key].c);
		strcat(text,buffer);
		strcat(text,",");
		sprintf(buffer,"%d",hashmap[key].parent->b);
		strcat(text,buffer);
		strcat(text,") \u27A1 ");

		strcat(text,"[");
		sprintf(buffer,"%d",hashmap[key].m - hashmap[key].parent->m);
		strcat(text,buffer);
		strcat(text,",");
		sprintf(buffer,"%d",hashmap[key].c - hashmap[key].parent->c);
		strcat(text,buffer);
		strcat(text,"]");

		strcat(text,"\u27A1 (");
		sprintf(buffer,"%d",hashmap[key].m);
		strcat(text,buffer);
		strcat(text,",");
		sprintf(buffer,"%d",hashmap[key].c);
		strcat(text,buffer);
		strcat(text,",");
		sprintf(buffer,"%d",hashmap[key].b);
		strcat(text,buffer);
		strcat(text,")");
	}

	return text;
}