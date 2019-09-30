#ifndef _GRAPH_H
#define _GRAPH_H

int **iniGraph(void);
void delGraph(int **graph);
void prtGraph(int **graph);
void gGraph(State *hashmap, int **graph);
void genDot(State *hashmap, int **graph, char *file);
void genViz(State *hashmap, int **graph, char *file);

#endif // _GRAPH_H