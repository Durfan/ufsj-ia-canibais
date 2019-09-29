#include "./includes/main.h"

Deque *dqcreate(void) {
	Deque *deque = malloc(sizeof(Deque));
    assert(deque);

	deque->head = NULL;
    deque->tail = NULL;
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
}

int dqpopHead(Deque *deque) {
	int key = deque->head->key;
	Node *node = deque->head;

	if (deque->head == deque->tail)
		deque->head = deque->tail = NULL;
	else
		deque->head = node->next;

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

	free(node);
	return key;
}

int dqpekHead(Deque *deque) {
	return deque->head->key;
}

int dqpekTail(Deque *deque) {
	return deque->tail->key;
}

void dqfree(Deque *deque) {
	free(deque);
}

bool dqEmpty(Deque *deque) {
	return deque->head == NULL;
}