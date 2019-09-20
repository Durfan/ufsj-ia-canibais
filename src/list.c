#include "./includes/main.h"

List *create(void) {
    List *list = malloc(sizeof(List));
	assert(list);
    list->head = NULL;
    list->tail = NULL;
    list->done = false;
    list->size = 0;
    return list;
}

void llpshHead(List *list, State state) {
    Node *node = malloc(sizeof(Node));
    assert(node);
    node->state = state;
    node->next = NULL;
    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
    }
    else {
        node->next = list->head;
        list->head = node;
    }
    list->size++;
}

void llpshTail(List *list, State state) {
    Node *node = malloc(sizeof(Node));
    assert(node);
    node->state = state;
    node->next = NULL;
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    }
    else {
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

void llpopHead(List *list) {
    if (isEmpty(list)) return;
    Node *ptr = list->head;
    if (list->head->next)
        list->head = list->head->next;
    else {
        list->head = NULL;
        list->tail = NULL;
    }
    free(ptr);

    if (list->size == 1)
        list->tail = list->head;
    list->size--;
}

void llpopTail(List *list) {
    if (isEmpty(list)) return;
    Node *curr, *prev = NULL;
    curr = list->head;
    while (curr->next) {
        prev = curr;
        curr = curr->next;
    }
    free(curr);

    if (prev)
        prev->next = NULL;
    else {
        list->head = NULL;
        list->tail = NULL;
    }
    if (list->size == 1)
        list->head = list->tail;
    list->size--;
}

void llprt(List *list) {
    if (isEmpty(list)) {
		printf(":Lista Vazia {}\n");
		return;
	}

    Node *ptr = list->head;
    if (!list->done) {
        printf(":{%d} expandir ----------:\n", list->size);
        while (ptr != NULL) {
            printf(" (%d,%d,%d)", ptr->state.m, ptr->state.c, ptr->state.b);
            ptr = ptr->next;
        }
        return;
    }

    State *parnt, child;
    int movex, movey;
    char *arrow = " \u27A1 ";

    printf("\n\n:{%d} expandidos --------:\n", list->size);
    while (ptr != NULL) {

        parnt = ptr->state.parent;
        child = ptr->state;
        if (parnt != NULL) {

            if (child.b) {
                movex = child.m - parnt->m;
                movey = child.c - parnt->c;
                printf(" (%d,%d,%d)", M - parnt->m, C - parnt->c, parnt->b);
                printf("%s[%d,%d]%s", arrow, movex, movey, arrow);
                printf("(%d,%d,%d)", child.m, child.c, child.b);
            } else {
                movex = parnt->m - child.m;
                movey = parnt->c - child.c;
                printf(" (%d,%d,%d)", parnt->m, parnt->c, parnt->b);
                printf("%s[%d,%d]%s", arrow, movex, movey, arrow);
                printf("(%d,%d,%d)", M - child.m, C - child.c, child.b);
            }

            printf(child.dinner ? " \u2620\n":"\n");
        }
        else {
            printf(" \u2205 --------------- ");
            printf("(%d,%d,%d)\n", child.m, child.c, child.b);
        }
        ptr = ptr->next;
    }
}

void llclr(List *list) {
    assert(list);
    Node *ptr, *node;
    node = list->head;
    while (node != NULL) {
        ptr = node->next;
        free(node);
        node = ptr;
    }
    free(list);
}

bool isEmpty(List *list) {
	return (list->head == NULL);
}