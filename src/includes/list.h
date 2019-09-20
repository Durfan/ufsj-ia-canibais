#ifndef _LIST_H
#define _LIST_H

typedef struct state_t {
	int m,c,b;
    bool dinner;
	struct state_t *parent;
} State;

typedef struct node_t {
    struct state_t state;
    struct node_t *next;
} Node;

typedef struct list_t {
    bool done;
    unsigned short size;
    struct node_t *head;
    struct node_t *tail;
} List;

List *create(void);
void llpshHead(List *list, State state);
void llpshTail(List *list, State state);
void llpopHead(List *list);
void llpopTail(List *list);
void llprt(List *list);
void llclr(List *list);
bool isEmpty(List *list);

#endif // _LIST_H