#include <stdio.h>
#include <malloc.h>

#define MAX_SIZE 10000
#define true 1
#define false 0
typedef int TYPE;
struct queue {
	TYPE *point;
	TYPE front;
	TYPE tail;
	int max_size;
};

int creat_queue(struct queue *q, int ca) {
	q->point = (TYPE*)malloc(sizeof(TYPE) * ca);
	if (!q->point) {
		perror("·ÖÅäÊ§°Ü\n");
		return -1;
	}
	q->front = 0;
	q->tail = 0;
	q->max_size = ca;
	return true;
}

int empty(struct queue* q) {
	if (q->front == q->tail) {
		return true;
	}
	return false;
}

int full(struct queue *q) {
	if ((q->tail + 1) % q->max_size == q->front) {
		return true;
	}
	return false;
}

int length(struct queue *q) {
	return (q->tail - q->front + q->max_size) % q->max_size;
}

int push(struct queue *q, TYPE elem) {
	if (full(q)) {
		return false;
	}
	q->point[q->tail] = elem;
	q->tail = (q->tail + 1) % q->max_size;
	return true;
}

int pop(struct queue*q, TYPE *elem) {
	if (empty(q)) {
		return false;
	}
	*elem = q->point[q->front];
	q->front = (q->front + 1) % q->max_size;
	return true;
}

void print_queue(struct queue *q) {
	int i = q->front;
	while (i != q->tail) {
		printf("%d ", q->point[i]);
		i = (i + 1) % q->max_size;
	}
	printf("\n");

}

void sort(struct queue *q, int(*function)(int, int)) {

}


