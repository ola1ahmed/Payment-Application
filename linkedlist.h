
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "STD_TYPES.h"

// Account Database Node
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
    struct ST_accountsDB_t *next; // Pointer to the next account node
} ST_accountsDB_t;

// Function prototypes
void addAccount(ST_accountsDB_t **head, float32 balance, EN_accountState_t state, const uint8 *pan);
void destroylist(ST_accountsDB_t **head);
void deleteAccount(ST_accountsDB_t **head, const uint8 *pan);
void printAccounts(const ST_accountsDB_t *head);

#endif

