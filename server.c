#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"


ST_accountsDB_t* accountsDB = NULL;  //head of accountsDB point to null
TransactionNode* transactionsDB = NULL;   //head of transactionsDB point to null

void addAccount(ST_accountsDB_t** head, float32 balance, EN_accountState_t state, const char* pan) {
	ST_accountsDB_t* newAccount = (ST_accountsDB_t*)malloc(sizeof(ST_accountsDB_t));
	if (newAccount != NULL)
	{
		newAccount->balance = balance;
		newAccount->state = state;
		strcpy((char*)newAccount->primaryAccountNumber, pan);
		newAccount->next = *head;
		*head = newAccount;
	}
}


EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t** accountReference) {
	ST_accountsDB_t* current = accountsDB;
	EN_serverError_t Server_Err_state=SERVER_OK;
	while (current != NULL) 
	{
		if (strcmp((char*)cardData->primaryAccountNumber, (char*)current->primaryAccountNumber) == 0) 
		{
			*accountReference = current;
			Server_Err_state=SERVER_OK;
			break;
		}
		current = current->next;
		Server_Err_state=ACCOUNT_NOT_FOUND;
	}
	*accountReference = NULL;
	return Server_Err_state ;
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference){
	EN_serverError_t Server_Err_state=SERVER_OK;
	if (accountReference->state == BLOCKED) 
	{
		Server_Err_state=BLOCKED_ACCOUNT;
	}
	else if (accountReference->state == RUNNING)
	{
		Server_Err_state=SERVER_OK;
	}
	return Server_Err_state;
}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t* accountReference) {
	EN_serverError_t Server_Err_state=SERVER_OK;
	if (accountReference->balance < termData->transAmount)
	{
		Server_Err_state=LOW_BALANCE;
	}
	else
	{
		Server_Err_state=SERVER_OK;
	}
	return Server_Err_state;
}

/*wrongggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg*/
EN_serverError_t saveTransaction(ST_transaction_t *transData) {
	TransactionNode* newTransaction = (TransactionNode*)malloc(sizeof(TransactionNode));
	EN_serverError_t Server_Err_state=SERVER_OK;
	if (newTransaction == NULL) 
	{
		Server_Err_state=SAVING_FAILED;
	}
	else
	{
		newTransaction->transaction = *transData;
		newTransaction->next = transactionsDB;
		transactionsDB = newTransaction;
		Server_Err_state=SERVER_OK;
	}

	return Server_Err_state;
}


EN_transStat_t recieveTransactionData(ST_transaction_t *transData) 
{
	ST_accountsDB_t* accountReference = NULL;
	
	if (isValidAccount(&transData->cardHolderData, &accountReference) == ACCOUNT_NOT_FOUND) 
	{
		return FRAUD_CARD;
	}
	if (isBlockedAccount(accountReference) == BLOCKED_ACCOUNT) 
	{
		return DECLINED_STOLEN_CARD;
	}
	if (isAmountAvailable(&transData->terminalData, accountReference) == LOW_BALANCE) 
	{
		return DECLINED_INSUFFECIENT_FUND;
	}
	accountReference->balance -= transData->terminalData.transAmount;

	if (saveTransaction(transData) == SAVING_FAILED) 
	{
		return INTERNAL_SERVER_ERROR;
	}

	return APPROVED;
}

void listSavedTransactions(void) {
	TransactionNode* current = transactionsDB;
	while (current != NULL) {
		printf("####################################################################################################\n");
		printf("Transaction Sequence Number: %u\n", current->transaction.transactionSequenceNumber);
		printf("Transaction Date: %s\n", current->transaction.terminalData.transactionDate);
		printf("Transaction Amount: %.2f\n", current->transaction.terminalData.transAmount);
		printf("Transaction State: %d\n", current->transaction.transState);
		printf("Terminal Max Amount: %.2f\n", current->transaction.terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", current->transaction.cardHolderData.cardHolderName);
		printf("PAN: %s\n", current->transaction.cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", current->transaction.cardHolderData.cardExpirationDate);
		printf("####################################################################################################\n");
		current = current->next;
	}
}

/*
--------------------------------------------------------------------------------

								TEST FUNCTION

--------------------------------------------------------------------------------
*/
#if (MODULE == TEST)
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

#endif

