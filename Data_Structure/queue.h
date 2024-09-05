
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../Library/STD_TYPES.h"
#include "../FILE_HANDLING/File_handling.h"


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
void Traverse_Queue(TransactionQueue *my_queue, void (*func)(ST_transaction_t *));
void print_Queue(ST_transaction_t *currentTransaction);
status_t Get_Queue_Count(TransactionQueue *my_queue, uint32 *QueueCount);

#endif

