#ifndef _GRAPH_H
#define _GRAPH_H

void gGraph(State *hashmap, int **graph);
void genDot(State *hashmap, int **graph);
void genViz(State *hashmap, int **graph);
void pGraph(int **graph, int size);

#endif // _GRAPH_H