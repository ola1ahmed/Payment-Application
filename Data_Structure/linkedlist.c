#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"


extern const uint8 *accountsFilename;

void addAccount(ST_accountsDB_t **head, float32 balance, EN_accountState_t state, const uint8 *pan)
{
    ST_accountsDB_t *newAccount = (ST_accountsDB_t *)malloc(sizeof(ST_accountsDB_t));
    if (newAccount != NULL)
    {
        newAccount->balance = balance;
        newAccount->state = state;
        strcpy((uint8 *)newAccount->primaryAccountNumber, (uint8 *)pan);
        newAccount->next = *head;
        *head = newAccount;
		saveAccountToFile(newAccount, accountsFilename);
    }
}

void destroylist(ST_accountsDB_t **head) {
    ST_accountsDB_t *current = *head;
    ST_accountsDB_t *nextNode;

    while (current != NULL) {
        nextNode = current->next;  
        free(current);             
        current = nextNode;        
    }

    *head = NULL; 
}
void deleteAccount(ST_accountsDB_t **head, const uint8 *pan)
{
    ST_accountsDB_t *current = *head;
    ST_accountsDB_t *previous = NULL;

    while (current != NULL)
    {
        if (strcmp((uint8 *)current->primaryAccountNumber, pan) == 0)
        {
            if (previous == NULL) 
            {
                *head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void printAccounts(const ST_accountsDB_t *head)
{
    const ST_accountsDB_t *current = head;
    while (current != NULL)
    {
        printf("Account PAN: %s, Balance: %.2f, State: %d\n", current->primaryAccountNumber, current->balance, current->state);
        current = current->next;
    }
}
