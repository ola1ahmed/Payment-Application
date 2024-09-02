
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "STD_TYPES.h"
#include "server.h"

  
typedef struct TransactionQueueNode
{
    ST_transaction_t transaction;
    struct TransactionQueueNode *next; 
} TransactionQueueNode;


typedef struct
{
    TransactionQueueNode *front;
    TransactionQueueNode *rear;
	uint8 size;
} TransactionQueue;


typedef enum {
    Queue_OK,
    Queue_NOK,
    Queue_Empty
} status_t;

// Function prototypes
TransactionQueue *Create_Queue(status_t *status);
status_t Destroy_Queue(TransactionQueue *my_queue);
status_t Enqueue_Element(TransactionQueue *my_queue, ST_transaction_t *transaction) ;
ST_transaction_t *Dequeue_Element(TransactionQueue *my_queue, status_t *status);
status_t Get_Queue_Count(TransactionQueue *my_queue, uint32 *QueueCount);

#endif

