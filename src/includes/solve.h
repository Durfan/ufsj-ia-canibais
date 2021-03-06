#ifndef _SOLVE_H
#define _SOLVE_H

State carry(State state, int m, int c);
State isDinner(State state);
bool feasible(State state, int m, int c);
void expand(State state, State *hashmap, Deque *deque, int **graph);
void largura(void);
void profund(void);
void bidirec(void);
void iteratv(void);
int limitada(int limit);
void genSol(State *hashmap, int **graph, char *file);
int stMapp(State *hashmap);

#endif // _SOLVE_H