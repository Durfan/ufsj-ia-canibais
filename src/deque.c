#include "./includes/main.h"

Deque *dqcreate(void) {
	Deque *deque = malloc(sizeof(Deque));
    assert(deque);

	deque->head = deque->tail = NULL;
	deque->size = 0;
	return deque;
}

void dqpshHead(Deque *deque, int key) {
	Node *node = malloc(sizeof(Node));
	assert(node);

	node->key = key;
	node->next = deque->head;
	node->prev = NULL;
	if (deque->tail == NULL) {
		deque->head = deque->tail = node;
	} else {
		deque->head->prev = node;
		deque->head = node;
	}
	deque->size++;
}

void dqpshTail(Deque *deque, int key) {
	Node *node = malloc(sizeof(Node));
	assert(node);

	node->key = key;
	node->prev = deque->tail;
	node->next = NULL;
	if (deque->head == NULL) {
		deque->head = deque->tail = node;
	} else {
		deque->tail->next = node;
		deque->tail = node;
	}
	deque->size++;
}

int dqpopHead(Deque *deque) {
	int key = deque->head->key;
	Node *node = deque->head;

	if (deque->head == deque->tail)
		deque->head = deque->tail = NULL;
	else
		deque->head = node->next;

	deque->size--;
	free(node);
	return key;
}

int dqpopTail(Deque *deque) {
	int key = deque->tail->key;
	Node *node = deque->tail;

	if (deque->head == deque->tail)
		deque->head = deque->tail = NULL;
	else
		deque->tail = node->prev;

	deque->size--;
	free(node);
	return key;
}

int dqpekHead(Deque *deque) {
	return deque->head ? deque->head->key : -1;
}

int dqpekTail(Deque *deque) {
	return deque->tail ? deque->tail->key : -1;
}

void dqprt(Deque *deque) {
	if (dqEmpty(deque))
		return;

	Node *node = deque->head;
	printf(" F{%02d}:", deque->size);
	while (node != NULL) {
		printf(" %02d", node->key);
		node = node->next;
	}
	printf("\n");
}

void dqclr(Deque *deque) {
	if (dqEmpty(deque)) {
		free(deque);
		return;
	}

	Node *delete;
	while (deque->head != NULL) {
        delete = deque->head;
        deque->head = deque->head->next;
        free(delete);
    }

	free(deque);
}

bool dqEmpty(Deque *deque) {
	return deque->head == NULL;
}