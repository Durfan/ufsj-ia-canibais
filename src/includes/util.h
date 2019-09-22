#ifndef _UTIL_H
#define _UTIL_H

int **iniArray(int n, int m);
void delArray(int **array, int n);
void pGraph(int **graph, int size);
void prtMap(State *hashmap);
char *stateInfo(State state, State *hashmap);

#endif // _UTIL_H