
#ifndef _STACK_H_
#define _STACK_H_

#include "../Library/STD_TYPES.h"
#include "../FILE_HANDLING/File_handling.h"

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
void Stack_Top(TransactionStack *stack, void (*func)(ST_transaction_t *)); 
void Traverse_Stack(TransactionStack *stack, void (*func)(ST_transaction_t *));
void print_Stack(ST_transaction_t *topNode);
uint32 isStackEmpty(const TransactionStack *stack,stutes_t *stutes);
void destroyStack(TransactionStack *stack);

#endif
