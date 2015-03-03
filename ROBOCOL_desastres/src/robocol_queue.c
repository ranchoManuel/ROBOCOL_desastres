#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "robocol_queue.h"

#define EMPTY -1
#define OVERFLOW 0

queue* init_robocol_queue(int bound) {
	queue *new_queue;
    new_queue = (queue *) malloc(sizeof(queue));
    new_queue->data = (int *) malloc(sizeof(int) *bound);
    new_queue->size = 0;
    new_queue->space = bound;
    new_queue->front = 0;
    new_queue->rear = -1;
    return new_queue;
}

int dequeue(queue* q) {
	if(q->size == 0)
		return EMPTY;
	else {
		int temp = q->data[q->front];
		q->size--; q->front++;
		if(q->front == q->space)
			q->front = 0;
		return temp;
	}
}

bool overflow(queue* q) {
	return q->size == q-> space;
}

bool enqueue(queue *q, int datum) {
	if(overflow(q))
		return OVERFLOW;
	else {
		q->size++;
		q->rear++;
		if(q->rear == q->space)
			q->rear = 0;
		q->data[q->rear] = datum;
	}
	return true;
}

int front(queue* q) {
	if(empty(q))
		return EMPTY;
	else
		return q->data[q->front];
} 

int rear(queue* q) {
	if(empty(q))
		return EMPTY;
	else
		return q->data[q->rear];
} 

bool empty(queue* q) {
	return q->front == q->rear;
}

void display(queue* q) {
	int i = q->front;
	while(i <= q->rear) {
		printf("%d ", q->data[i]);
		i++;
	}
	printf("\n");
}