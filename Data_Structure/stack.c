
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

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


void Stack_Top(TransactionStack *stack, void (*func)(ST_transaction_t *)) {
    if (stack != NULL) 
	{
        TransactionStackNode *topNode = stack->top;
        
        func(&topNode->transaction);
        topNode = topNode->next;
        
    }
	else
	{
		printf("No Transactions avilable \n");
	}
}

void Traverse_Stack(TransactionStack *stack, void (*func)(ST_transaction_t *)) {
    if (stack != NULL) 
	{
        TransactionStackNode *topNode = stack->top;
        while (topNode != NULL) 
		{
            func(&topNode->transaction);
            topNode = topNode->next;
        }
    }
	else
	{
		printf("No Transactions avilable \n");
	}
}

void print_Stack(ST_transaction_t *currentTransaction)
{
		printf("Transaction Sequence Number: %u\n", currentTransaction->transactionSequenceNumber);
		printf("Cardholder Name: %s\n", currentTransaction->cardHolderData.cardHolderName);
		printf("PAN: %s\n", currentTransaction->cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", currentTransaction->cardHolderData.cardExpirationDate);
		printf("Transaction Date: %s\n", currentTransaction->terminalData.transactionDate);
		printf("Transaction Amount: %.2f\n", currentTransaction->terminalData.transAmount);
		printf("Terminal Max Amount: %.2f\n", currentTransaction->terminalData.maxTransAmount);
		printf("Transaction State: %d\n", currentTransaction->transState);
		printf("###########################################\n");
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