#ifndef _DATA_BASE_H_
#define _DATA_BASE_H_

#include "../Library/STD_TYPES.h"
#define MODULE   TEST
#define TEST     1
#define USER     2



typedef enum
{
    RUNNING,
    BLOCKED
} EN_accountState_t;

typedef struct ST_accountsDB_t
{
    float32 balance;
    EN_accountState_t state;
    uint8 primaryAccountNumber[20];
    struct ST_accountsDB_t *next; 
} ST_accountsDB_t;

typedef struct ST_cardData_t
{
 uint8 cardHolderName[25];
 uint8 primaryAccountNumber[20];
 uint8 cardExpirationDate[6];
}ST_cardData_t;

typedef struct ST_terminalData_t
{
	float32 transAmount;
	float32 maxTransAmount;
	uint8 transactionDate[11];
	
}ST_terminalData_t;

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
typedef struct TransactionQueueNode
{
    ST_transaction_t transaction;
    struct TransactionQueueNode *next; 
} TransactionQueueNode;

typedef struct
{
    TransactionQueueNode *front;
    TransactionQueueNode *rear;
	uint8 size;
} TransactionQueue;
typedef struct TransactionStackNode
{
    ST_transaction_t transaction;
    struct TransactionStackNode *next; 
} TransactionStackNode;


typedef struct
{
    TransactionStackNode *top;
} TransactionStack;
#endif