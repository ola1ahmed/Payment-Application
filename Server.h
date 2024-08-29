// server.h
#ifndef _SERVER_H_
#define _SERVER_H_

#include "STD_TYPES.h"
#include "Terminal.h"
#include "Card.h"


typedef enum EN_transState_t {
	APPROVED,
	DECLINED_INSUFFECIENT_FUND,
	DECLINED_STOLEN_CARD,
	FRAUD_CARD,
	INTERNAL_SERVER_ERROR
} EN_transStat_t;


typedef struct ST_transaction_t {
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transStat_t transState;
	uint32 transactionSequenceNumber;
} ST_transaction_t;

typedef struct TransactionNode {
    ST_transaction_t transaction;
    struct TransactionNode* next;
} TransactionNode;

typedef enum EN_serverError_t {
	SERVER_OK,
	SAVING_FAILED,
	TRANSACTION_NOT_FOUND,
	ACCOUNT_NOT_FOUND,
	LOW_BALANCE,
	BLOCKED_ACCOUNT,
	NULL_POINTER
} EN_serverError_t;


typedef enum EN_accountState_t {
	RUNNING,
	BLOCKED
} EN_accountState_t;


typedef struct ST_accountsDB_t {
	float32 balance;
	EN_accountState_t state;
	uint8 primaryAccountNumber[20];
	struct ST_accountsDB_t *next;  
} ST_accountsDB_t;
/*
--------------------------------------------------------------------------------

								public FUNCTION

--------------------------------------------------------------------------------
*/
EN_transStat_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t** accountReference);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t* accountReference);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
void listSavedTransactions(void);
/*
--------------------------------------------------------------------------------

								privite TEST FUNCTION

--------------------------------------------------------------------------------
*/
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);

#endif
