#ifndef _DEQUE_H
#define _DEQUE_H

typedef struct node_t {
    int key;
	struct node_t *next;
	struct node_t *prev;
} Node;

typedef struct deque_t {
	int size;
	struct node_t *head;
	struct node_t *tail;
} Deque;

Deque *dqcreate(void);
void dqpshHead(Deque *deque, int key);
void dqpshTail(Deque *deque, int key);
int dqpopHead(Deque *deque);
int dqpopTail(Deque *deque);
int dqpekHead(Deque *deque);
int dqpekTail(Deque *deque);
void dqprt(Deque *deque);
void dqclr(Deque *deque);
bool dqEmpty(Deque *deque);

#endif // _DEQUE_H 
