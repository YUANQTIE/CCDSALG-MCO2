/***********************************************************************************
**********************
Developed by: 
Yuan Miguel A. Panlilio, 12413135
Nigel Henry S. So, 12413801
Princess Ayesa A. Tullao, 12412112
************************************************************************************
*********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/*Function that initializes the queue indices.
	@param queue - the queue whose indicies will be initialized.
*/

void Create(Queue *queue){
    queue->front = 0;
    queue->rear = 0;
}

/*Function that enqueues an entry to the rear of the queue.
	@param queue - the queue where the entry will be enqueued in.
    @param entry - the entry to be added to the queue.
*/

void Enqueue(Queue *queue, char entry[]){
    if (QueueFull(queue)){
        printf("Overflow.\n");
    }
    else{
        strcpy(queue->entry[queue->rear], entry);
        queue->rear++;
    }
}

/*Function that dequeues an entry from the head of the queue.
	@param queue - the queue whose head will be dequeued.
    @return value at the head of the queue.
*/

char* Dequeue(Queue *queue){
    char* value = NULL;
    if (QueueEmpty(queue)){
        printf("Underflow.\n");
    }
    else{
        queue->front++;
        value = queue->entry[queue->front - 1];
    }

    return value;
}

/*Function that allows to get a peek of the value at the head of the queue.
	@param queue - the queue whose head will be checked.
    @return value at the head of the queue.
*/

char* QueueHead(Queue *queue){
    char* value = NULL;
    if (QueueEmpty(queue)){
        printf("Underflow.\n");
    }
    else{
        value = queue->entry[queue->front]; 
    }

    return value;
}

/*Function that allows that checks if the queue is empty.
	@param queue - the queue whose contents will be checked.
    @return 1 if the index at the head of the queue is equal to index at the tail of the queue.
*/

int QueueEmpty(Queue *queue){
    return queue->front == queue->rear;
}

/*Function that allows that checks if the queue is full.
	@param queue - the queue whose contents will be checked.
    @return 1 if the index at the rear is already before the index at the head.
*/

int QueueFull(Queue *queue){
    return queue->front == (queue->rear + 1) % MAX_VERTICES;
}
