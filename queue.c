#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void Create(Queue *queue){
    queue->front = 0;
    queue->rear = 0;
}

void Enqueue(Queue *queue, char entry[]){
    if (QueueFull(queue)){
        printf("Overflow.\n");
    }
    else{
        strcpy(queue->entry[queue->rear], entry);
        queue->rear++;
    }
}

char* Dequeue(Queue *queue){
    if (QueueEmpty(queue)){
        printf("Underflow.\n");
        return NULL;
    }
    else{
        queue->front++;
        return queue->entry[queue->front - 1];
    }
}


char* QueueHead(Queue *queue){

    if (QueueEmpty(queue)){
        printf("Underflow.\n");
        return NULL;
    }
    else{
        return queue->entry[queue->front]; 
    }
}

char* QueueTail(Queue *queue){

    if (QueueEmpty(queue)){
        printf("Underflow.\n");
        return NULL;
    }
    else{
        return queue->entry[queue->rear]; 
    }
}

int QueueEmpty(Queue *queue){
    return queue->front == queue->rear;
}
int QueueFull(Queue *queue){
    return queue->front == (queue->rear + 1) % MAX_VERTICES;
}