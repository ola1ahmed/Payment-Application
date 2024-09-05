
#ifndef _SERVER_H_
#define _SERVER_H_



#include "../Library/STD_TYPES.h"

#include "../TERMINAL/Terminal.h"

#include "../Data_Structure/linkedlist.h"
#include "../Data_Structure/queue.h"
#include "../Data_Structure/stack.h"



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
void listSavedTransactions(void);
void lastSavedTransactions (void);
/*
--------------------------------------------------------------------------------

								TEST FUNCTION

--------------------------------------------------------------------------------
*/
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void recieveTransactionDataTest(void);
void listSavedTransactionsTest(void);
#endif

