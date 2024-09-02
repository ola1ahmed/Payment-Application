#include "queue.h"
#include <stdio.h>
#include <stdlib.h>



TransactionQueue *Create_Queue(status_t *status) {
    *status = Queue_NOK;
    TransactionQueue *my_queue = (TransactionQueue *)malloc(sizeof(TransactionQueue));
    if (my_queue != NULL) 
	{
        my_queue->front = NULL;
        my_queue->rear = NULL;
        my_queue->size = 0;
        *status = Queue_OK;
    }
    return my_queue;
}


status_t Destroy_Queue(TransactionQueue *my_queue) {
    status_t status = Queue_NOK;
    if (my_queue != NULL) 
	{
        TransactionQueueNode *tempPtr = NULL;
        while (my_queue->size > 0) 
		{
            tempPtr = my_queue->front;
            my_queue->front = my_queue->front->next;
            free(tempPtr);
            my_queue->size--;
        }
        free(my_queue);
        status = Queue_OK;
    }
    return status;
}

status_t Enqueue_Element(TransactionQueue *my_queue, ST_transaction_t *transaction) {
    status_t status = Queue_NOK;
    if (my_queue != NULL) 
	{
        TransactionQueueNode *newNode = (TransactionQueueNode *)malloc(sizeof(TransactionQueueNode));
        if (newNode != NULL) 
		{
            newNode->transaction = *transaction;
            newNode->next = NULL;
            if (my_queue->size != 0)
			{
                my_queue->rear->next = newNode;
                my_queue->rear = newNode;
            } 
			else
			{
                my_queue->rear = newNode;
                my_queue->front = newNode;
            }
            my_queue->size++;
            status = Queue_OK;
        }
    }
    return status;
}

ST_transaction_t *Dequeue_Element(TransactionQueue *my_queue, status_t *status) {
    ST_transaction_t *transaction = NULL;
    *status = Queue_NOK;
    if (my_queue != NULL) 
	{
        if (my_queue->size == 0) 
		{
            *status = Queue_Empty;
        } 
		else 
		{
            TransactionQueueNode *tempPtr = my_queue->front;
            transaction = (ST_transaction_t *)malloc(sizeof(ST_transaction_t));
            if (transaction != NULL) 
			{
                *transaction = my_queue->front->transaction;
            }
            my_queue->front = my_queue->front->next;
            free(tempPtr);
            my_queue->size--;
            if (my_queue->size == 0) 
			{
                my_queue->front = NULL;
                my_queue->rear = NULL;
            }
            *status = Queue_OK;
        }
    }
    return transaction;
}


void Traverse_Queue(TransactionQueue *my_queue, void (*func)(ST_transaction_t *)) {
    if (my_queue != NULL) 
	{
        TransactionQueueNode *current = my_queue->front;
        while (current != NULL) 
		{
            func(&current->transaction);
            current = current->next;
        }
    }
}

status_t Get_Queue_Count(TransactionQueue *my_queue, uint32 *QueueCount) {
    status_t status = Queue_NOK;
    if (my_queue != NULL) 
	{
        *QueueCount = my_queue->size;
        status = Queue_OK;
    }
    return status;
}