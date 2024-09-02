
#ifndef _SERVER_H_
#define _SERVER_H_



#include "STD_TYPES.h"
#include "Card.h"
#include "Terminal.h"


typedef struct ST_transaction_t ST_transaction_t;
typedef struct ST_accountsDB_t ST_accountsDB_t;

typedef enum EN_transState_t
{
	APPROVED, 
	DECLINED_INSUFFECIENT_FUND,
	DECLINED_STOLEN_CARD,
	FRAUD_CARD, 
	INTERNAL_SERVER_ERROR
}EN_transStat_t;

typedef enum EN_serverError_t
{
	SERVER_OK,
	SAVING_FAILED,
	TRANSACTION_NOT_FOUND,
	ACCOUNT_NOT_FOUND,
	LOW_BALANCE,
	BLOCKED_ACCOUNT
}EN_serverError_t ;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    uint32 transactionSequenceNumber;
    EN_serverError_t transState;
} ST_transaction_t;
/*
--------------------------------------------------------------------------------

								public FUNCTION

--------------------------------------------------------------------------------
*/

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountReference);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_transStat_t recieveTransactionData(ST_transaction_t *transData);
//void listSavedTransactions(TransactionStack *stack) 
void listSavedTransactions(void);
/*
--------------------------------------------------------------------------------

								TEST FUNCTION

--------------------------------------------------------------------------------
*/
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void recieveTransactionDataTest(void);
#endif

