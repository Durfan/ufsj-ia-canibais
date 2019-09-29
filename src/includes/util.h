#ifndef _UTIL_H
#define _UTIL_H

void prtFOOclk(struct timeval tv1, struct timeval tv2);
double ftempo(struct timeval tv1, struct timeval tv2);
void prtMap(State *hashmap);

#endif // _UTIL_H