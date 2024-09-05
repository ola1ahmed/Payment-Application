
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "../Library/STD_TYPES.h"

#include "../FILE_HANDLING/File_handling.h"

void addAccount(ST_accountsDB_t **head, float32 balance, EN_accountState_t state, const uint8 *pan);
void destroylist(ST_accountsDB_t **head);
void deleteAccount(ST_accountsDB_t **head, const uint8 *pan);
void printAccounts(const ST_accountsDB_t *head);

#endif

