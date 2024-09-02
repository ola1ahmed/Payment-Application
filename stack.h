
#ifndef _STACK_H_
#define _STACK_H_

#include "STD_TYPES.h"
#include "server.h"


typedef struct TransactionStackNode
{
    ST_transaction_t transaction;
    struct TransactionStackNode *next; 
} TransactionStackNode;


typedef struct
{
    TransactionStackNode *top;
} TransactionStack;

typedef enum
{
	S_NOK=0,
	S_OK,
	S_EMPTY,
	S_FULL,
	S_NULL,
}stutes_t;


TransactionStack* CreateStack(stutes_t *stutes);
stutes_t pushTransaction(TransactionStack *stack, ST_transaction_t *transaction);
ST_transaction_t popTransaction(TransactionStack *stack,stutes_t *stutes);
uint32 isStackEmpty(const TransactionStack *stack,stutes_t *stutes);
void destroyStack(TransactionStack *stack);

#endif
