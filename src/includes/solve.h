#ifndef _SOLVE_H
#define _SOLVE_H

bool feasible(State state, int my, int cy);
void isDinner(State *state);
void carry(State *state, int m, int c);
void expand(State state, State *hashmap);

#endif // _SOLVE_H