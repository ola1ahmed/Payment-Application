#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


TransactionStack* CreateStack(stutes_t *stutes)
{
	*stutes = S_NOK;
    TransactionStack *my_stack = (TransactionStack *)malloc(sizeof(TransactionStack));
    if (my_stack != NULL) 
	{
        my_stack->top = NULL;
        *stutes = S_OK;
    }
    return my_stack;
    
}


stutes_t pushTransaction(TransactionStack *stack, ST_transaction_t *transaction)
{
	stutes_t status;
	status = S_NOK;
    TransactionStackNode *newNode = (TransactionStackNode *)malloc(sizeof(TransactionStackNode));
    if (newNode != NULL)
    {
        newNode->transaction = *transaction;
        newNode->next = stack->top;
        stack->top = newNode;
		status = S_OK;
    }
	return status;
}


ST_transaction_t popTransaction(TransactionStack *stack,stutes_t *stutes)
{
	*stutes = S_NOK;
    if (stack->top == NULL)
    {
        printf("Stack is empty.\n");
        ST_transaction_t emptyTransaction = {0};
		*stutes =S_EMPTY;
        return emptyTransaction;
    }

    TransactionStackNode *topNode = stack->top;
    ST_transaction_t transaction = topNode->transaction;
    stack->top = topNode->next;
    free(topNode);
	*stutes = S_OK;
    return transaction;
}

uint32 isStackEmpty(const TransactionStack *stack,stutes_t *stutes)
{
	*stutes =S_EMPTY;
    return stack->top == NULL;
}
void destroyStack(TransactionStack *stack)
{
    while (stack->top != NULL)
    {
        TransactionStackNode *temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    free(stack);
}