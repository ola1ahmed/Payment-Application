#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "queue.h"
#include "stack.h"
#include "linkedlist.h"
#include "file_handling.h" 

extern ST_accountsDB_t *accountsDB ;
extern TransactionQueue *transactionsDB;  
//extern TransactionStack transactionStack; 
extern TransactionStack *stack;
const char *transactionFilename = "transactions.txt";
 const uint8 *accountsFilename = "accounts.txt";
extern uint32 lastSequenceNumber ;


EN_transStat_t recieveTransactionData(ST_transaction_t *transData)
{
    ST_accountsDB_t *accountReference = NULL;
    EN_serverError_t Server_Err_state = FRAUD_CARD; 
	
    if (isValidAccount(&transData->cardHolderData, &accountReference) != ACCOUNT_NOT_FOUND)
    {
		
        if (isBlockedAccount(accountReference) != BLOCKED_ACCOUNT)
        {
			
            if (isAmountAvailable(&transData->terminalData, accountReference) != LOW_BALANCE)
            {
				
                accountReference->balance -= transData->terminalData.transAmount;
				updateAccountToFile(accountsDB,accountsFilename);
				
				
                if (saveTransaction(transData) == SERVER_OK)
                {
					
					
                    Server_Err_state = APPROVED;
                }
                else
                {
					
                    Server_Err_state = INTERNAL_SERVER_ERROR;
                }
            }
            else
            {
				
                Server_Err_state = DECLINED_INSUFFECIENT_FUND;
            }
        }
        else
        {	
			
            Server_Err_state = DECLINED_STOLEN_CARD;
        }
    }
	else
	{
		
	}
	
    return Server_Err_state;
}



EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
	status_t status;

    if (transData == NULL)
    {
        printf("INTERNAL_SERVER_ERROR1 \t");
        return INTERNAL_SERVER_ERROR;
    }

    FILE *file = fopen(transactionFilename, "a");
    if (file == NULL)
    {
        printf("INTERNAL_SERVER_ERROR2 \t");
        return INTERNAL_SERVER_ERROR;
    }

    
    if (transactionsDB->rear != NULL) 
	{
        lastSequenceNumber = transactionsDB->rear->transaction.transactionSequenceNumber;
    }

    transData->transactionSequenceNumber = lastSequenceNumber + 1;
	transData->transState = APPROVED;
	
     status = Enqueue_Element(transactionsDB, transData);
	 pushTransaction(stack, transData);
    if (status != Queue_OK)
    {
        printf("Failed to enqueue transaction\n");
        fclose(file);
        return SAVING_FAILED;
    }

    fprintf(file, "Transaction Sequence Number: %u\n", transData->transactionSequenceNumber);
    fprintf(file, "Cardholder Name: %s\n", transData->cardHolderData.cardHolderName);
    fprintf(file, "PAN: %s\n", transData->cardHolderData.primaryAccountNumber);
    fprintf(file, "Card Expiration Date: %s\n", transData->cardHolderData.cardExpirationDate);
    fprintf(file, "Transaction Date: %s\n", transData->terminalData.transactionDate);
    fprintf(file, "Transaction Amount: %.2f\n", transData->terminalData.transAmount);
    fprintf(file, "Terminal Max Amount: %.2f\n", transData->terminalData.maxTransAmount);
    fprintf(file, "Transaction State: %d\n", transData->transState);
    fprintf(file, "###########################################\n");

    
    fclose(file);

    return SERVER_OK;
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountReference)
{
	EN_serverError_t Server_Err_state=SERVER_OK;
    ST_accountsDB_t *current = accountsDB;
		while (current != NULL)
		{
			if (strcmp((char *)cardData->primaryAccountNumber, (char *)current->primaryAccountNumber) == 0)
			{
				*accountReference = current;
				Server_Err_state=SERVER_OK;
				return Server_Err_state;
			}
			current = current->next;
			Server_Err_state=ACCOUNT_NOT_FOUND;
		}
		*accountReference = NULL;
	
    return Server_Err_state;
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference)
{
	EN_serverError_t Server_Err_state=SERVER_OK;
	if(accountReference!=NULL)
	{
		if (accountReference->state == BLOCKED)
		{
			Server_Err_state=BLOCKED_ACCOUNT;
		}
		else
		{
			Server_Err_state=SERVER_OK;
		}
	}
	else
	{
		Server_Err_state=BLOCKED_ACCOUNT;
	}
    return Server_Err_state;
}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference)
{
	EN_serverError_t Server_Err_state=SERVER_OK;
	if(accountReference!=NULL)
	{
		if (accountReference->balance < termData->transAmount)
		{
			Server_Err_state=LOW_BALANCE;
		}
		else
		{
			Server_Err_state=SERVER_OK;
		}
	}	
	else
	{
		Server_Err_state=LOW_BALANCE;
	}
    return Server_Err_state;
}
void listSavedTransactions(void)
{
    if (stack->top == NULL) {
        printf("No transactions available.\n");
        return;
    }

    TransactionStackNode *currentNode = stack->top;
    while (currentNode != NULL) {
        ST_transaction_t *currentTransaction = &currentNode->transaction;
        printf("Transaction Sequence Number: %u\n", currentTransaction->transactionSequenceNumber);
        printf("Cardholder Name: %s\n", currentTransaction->cardHolderData.cardHolderName);
        printf("PAN: %s\n", currentTransaction->cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", currentTransaction->cardHolderData.cardExpirationDate);
        printf("Transaction Date: %s\n", currentTransaction->terminalData.transactionDate);
        printf("Transaction Amount: %.2f\n", currentTransaction->terminalData.transAmount);
        printf("Terminal Max Amount: %.2f\n", currentTransaction->terminalData.maxTransAmount);
        printf("Transaction State: %d\n", currentTransaction->transState);
        printf("###########################################\n");

        currentNode = currentNode->next; 
    }
}


/*
--------------------------------------------------------------------------------

								TEST FUNCTION

--------------------------------------------------------------------------------
*/
#if (MODULE == TEST)

void recieveTransactionDataTest(void)
{
    ST_transaction_t transaction;
    EN_transStat_t result;
    printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\t\t recieveTransactionDataTest\t\t\t\n");
 
    printf("\nTest Case 1:\n");
	 strcpy((char *)transaction.cardHolderData.cardHolderName,"ahmed aly ahmed aly amr");
    strcpy((char *)transaction.cardHolderData.primaryAccountNumber, "12345678901234567");
	strcpy((char *)transaction.cardHolderData.cardExpirationDate,"12/26");
    transaction.terminalData.transAmount = 100.0;
    strcpy((char *)transaction.terminalData.transactionDate, "12/12/2024");
    transaction.terminalData.maxTransAmount = 1000.0;
    result = recieveTransactionData(&transaction);
	transaction.transState=result;
    printf("Expected: APPROVED\n");

    switch(result)
    {
        case APPROVED: printf("Actual: APPROVED\n"); break;
        case DECLINED_INSUFFECIENT_FUND: printf("Actual: DECLINED_INSUFFECIENT_FUND\n"); break;
        case DECLINED_STOLEN_CARD: printf("Actual: DECLINED_STOLEN_CARD\n"); break;
        case FRAUD_CARD: printf("Actual: FRAUD_CARD\n"); break;
        case INTERNAL_SERVER_ERROR: printf("Actual: INTERNAL_SERVER_ERROR\n"); break;
        default: printf("Actual: UNKNOWN ERROR\n"); break;
    }

    printf("\nTest Case 2:\n");
    strcpy((char *)transaction.cardHolderData.primaryAccountNumber, "11111122201234567");

    result = recieveTransactionData(&transaction);
    printf("Expected: DECLINED_STOLEN_CARD\n");

    switch(result)
    {
        case APPROVED: printf("Actual: APPROVED\n"); break;
        case DECLINED_INSUFFECIENT_FUND: printf("Actual: DECLINED_INSUFFECIENT_FUND\n"); break;
        case DECLINED_STOLEN_CARD: printf("Actual: DECLINED_STOLEN_CARD\n"); break;
        case FRAUD_CARD: printf("Actual: FRAUD_CARD\n"); break;
        case INTERNAL_SERVER_ERROR: printf("Actual: INTERNAL_SERVER_ERROR\n"); break;
        default: printf("Actual: UNKNOWN ERROR\n"); break;
    }

    printf("\nTest Case 3:\n");
    strcpy((char *)transaction.cardHolderData.primaryAccountNumber, "12345678901234567");
    transaction.terminalData.transAmount = 6000.0; 

    result = recieveTransactionData(&transaction);
    printf("Expected: DECLINED_INSUFFECIENT_FUND\n");

    switch(result)
    {
        case APPROVED: printf("Actual: APPROVED\n"); break;
        case DECLINED_INSUFFECIENT_FUND: printf("Actual: DECLINED_INSUFFECIENT_FUND\n"); break;
        case DECLINED_STOLEN_CARD: printf("Actual: DECLINED_STOLEN_CARD\n"); break;
        case FRAUD_CARD: printf("Actual: FRAUD_CARD\n"); break;
        case INTERNAL_SERVER_ERROR: printf("Actual: INTERNAL_SERVER_ERROR\n"); break;
        default: printf("Actual: UNKNOWN ERROR\n"); break;
    }
}



void isValidAccountTest(void) {
    ST_cardData_t cardData;
    ST_accountsDB_t* accountReference;
    EN_serverError_t result;
    
	printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\t\tisValidAccountTest\t\t\t\n");

    printf("\nTest Case 1:\n");
    strcpy((char*)cardData.primaryAccountNumber, "1234567890123456789");
    result = isValidAccount(&cardData, &accountReference);
    printf("Expected SERVER_OK\n");
	printf("Actual: %s\n", (result == SERVER_OK) ? "SERVER_OK" : "ACCOUNT_NOT_FOUND");
    
    printf("\nTest Case 2:\n");
    strcpy((char*)cardData.primaryAccountNumber, "0000000000000000000");
    result = isValidAccount(&cardData, &accountReference);
	 printf("Expected ACCOUNT_NOT_FOUND\n");
    printf("Actual: %s\n", (result == ACCOUNT_NOT_FOUND) ? "ACCOUNT_NOT_FOUND" : "SERVER_OK");
}
void isBlockedAccountTest(void){
	
    ST_accountsDB_t* accountReference;
    EN_serverError_t result;
	accountReference = (ST_accountsDB_t*) malloc(sizeof(ST_accountsDB_t));
    if (accountReference == NULL) 
	{
        printf("Memory allocation failed!\n");
        return;
    }
    
	printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\t\tisBlockedAccountTest\t\t\t\n");

    printf("\nTest Case 1:\n");
    accountReference->state= RUNNING;
    result = isBlockedAccount(accountReference);
    printf("Expected SERVER_OK\n");
	printf("Actual: %s\n", (result == SERVER_OK) ? "SERVER_OK" : "BLOCKED_ACCOUNT");
    
    printf("\nTest Case 2:\n");
    accountReference->state = BLOCKED;
    result = isBlockedAccount(accountReference);
	printf("Expected BLOCKED_ACCOUNT\n");
    printf("Actual: %s\n", (result == SERVER_OK) ? "SERVER_OK" : "BLOCKED_ACCOUNT");
	
	free(accountReference);
}

void isAmountAvailableTest(void){
	
	ST_terminalData_t termData;
	ST_accountsDB_t* accountReference;
	EN_serverError_t result;
	
	accountReference = (ST_accountsDB_t*) malloc(sizeof(ST_accountsDB_t));
    if (accountReference == NULL) 
	{
        printf("Memory allocation failed!\n");
        return;
    }
    
	printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\t\tisAmountAvailableTest\t\t\t\n");

	
    printf("\nTest Case 1:\n");
	termData.transAmount=900;
	accountReference->balance=1000;
	result =isAmountAvailable(&termData,accountReference);
	printf("Expected SERVER_OK\n");
	printf("Actual: %s\n", (result == SERVER_OK) ? "SERVER_OK" : "LOW_BALANCE");
	
	printf("\nTest Case 2:\n");
	termData.transAmount=1000;
	accountReference->balance=900;
	result =isAmountAvailable(&termData,accountReference);
	printf("Expected LOW_BALANCE\n");
	printf("Actual: %s\n", (result == SERVER_OK) ? "SERVER_OK" : "LOW_BALANCE");
	free(accountReference);
}


void listSavedTransactionsTest(void)
{
	printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\t\tlistSavedTransactionsTest\t\t\t\n");
    listSavedTransactions();
}
void saveTransactionTest(void)
{
    ST_transaction_t transaction;
    EN_serverError_t result;

	printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\t\tsaveTransactionTest\t\t\t\n");
    
    strcpy((char *)transaction.cardHolderData.primaryAccountNumber, "1234567890123456789");
    transaction.terminalData.transAmount = 100.0;
    transaction.transState = APPROVED;

    
    result = saveTransaction(&transaction);
	printf("\nTest Case 1:\n");
	printf("Expected SERVER_OK\n");
    printf("Actual: %s\n", (result == SERVER_OK) ? "SERVER_OK" : "SAVING_FAILED");
}
#endif

