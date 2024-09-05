#ifndef _FILE_HANDLING_H_
#define _FILE_HANDLING_H_

#include "../Library/STD_TYPES.h"
#include "database.h"

EN_serverError_t saveAccountToFile(ST_accountsDB_t *account, const uint8 *filename);
EN_serverError_t loadAccountsFromFile(ST_accountsDB_t **head, const uint8 *filename);
EN_serverError_t updateAccountToFile(ST_accountsDB_t *account, const uint8 *filename);


EN_serverError_t saveTransactionToFile(ST_transaction_t *transData, const uint8 *filename);
EN_serverError_t loadTransactionsFromFile(TransactionStack *stack,TransactionQueue *queue, const uint8 *filename);



#endif





