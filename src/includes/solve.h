#ifndef _SOLVE_H
#define _SOLVE_H

State carry(State state, int m, int c);
State isDinner(State state);
bool feasible(State state, int my, int cy);
void expand(State state, State *hashmap);
void solve(State *hashmap);

#endif // _SOLVE_H