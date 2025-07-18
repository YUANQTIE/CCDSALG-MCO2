#ifndef QUEUE_H
#define QUEUE_H
#define MAX_VERTICES 20
#define MAX_EDGES 190
#include<string.h>
typedef struct {
	char entry[MAX_VERTICES][100];
    int front;
    int rear;
} Queue;

void Create(Queue *queue);
void Enqueue(Queue *queue, char entry[]);
char* Dequeue(Queue *queue);
char* QueueHead(Queue *queue);
char* QueueTail(Queue *queue);
int QueueEmpty(Queue *queue);
int QueueFull(Queue *queue);

#endif
