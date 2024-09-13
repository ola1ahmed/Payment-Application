
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "File_handling.h"

#include "../Data_Structure/linkedlist.h"
#include "../Data_Structure/queue.h"
#include "../Data_Structure/stack.h"

extern uint32 lastSequenceNumber ;

const char *transactionFilename = "transactions.txt";
const uint8 *accountsFilename = "accounts.txt";


EN_serverError_t loadTransactionsFromFile(TransactionStack *stack,TransactionQueue *queue, const uint8 *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return TRANSACTION_NOT_FOUND;
    }

    ST_transaction_t transaction;
    char line[256];
    int fieldsRead;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Check for the start of a transaction block
        if (strncmp(line, "Transaction Sequence Number:", 28) == 0)
        {
            fieldsRead = sscanf(line, "Transaction Sequence Number: %u",
                                &transaction.transactionSequenceNumber);

            if (fieldsRead == 1)
            {
                fgets(line, sizeof(line), file); 
                sscanf(line, "Cardholder Name: %[^\n]", transaction.cardHolderData.cardHolderName);

                fgets(line, sizeof(line), file); 
                sscanf(line, "PAN: %[^\n]", transaction.cardHolderData.primaryAccountNumber);

                fgets(line, sizeof(line), file); 
                sscanf(line, "Card Expiration Date: %[^\n]", transaction.cardHolderData.cardExpirationDate);

                fgets(line, sizeof(line), file); 
                sscanf(line, "Transaction Date: %[^\n]", transaction.terminalData.transactionDate);

                fgets(line, sizeof(line), file); 
                sscanf(line, "Transaction Amount: %f", &transaction.terminalData.transAmount);

                fgets(line, sizeof(line), file); 
                sscanf(line, "Terminal Max Amount: %f", &transaction.terminalData.maxTransAmount);

                fgets(line, sizeof(line), file);
                sscanf(line, "Transaction State: %d", (int *)&transaction.transState);

               
                fgets(line, sizeof(line), file);

                ST_transaction_t *newTransaction = malloc(sizeof(ST_transaction_t));
                if (newTransaction == NULL)
                {
                    perror("Error allocating memory");
                    fclose(file);
                    return SAVING_FAILED;
                }
                *newTransaction = transaction;
				
                if (transaction.transactionSequenceNumber > lastSequenceNumber)
                {
                    lastSequenceNumber = transaction.transactionSequenceNumber;
                }
                Enqueue_Element(queue, newTransaction);

				pushTransaction(stack, newTransaction);
            }
            else
            {
                printf("Error: Incorrect format for transaction sequence number.\n");
            }
        }
    }

    fclose(file);
    return SERVER_OK;
}


EN_serverError_t saveAccountToFile(ST_accountsDB_t *account, const uint8 *filename)
{
    FILE *file = fopen(filename, "a");  // Open file in append mode
    if (file == NULL)
    {
        perror("Error opening file");
        return SAVING_FAILED;
    }

    // Save account information in a comma-separated format
    fprintf(file, "%.2f,%d,%s,%s,%s\n",
            account->balance,
            account->state,
            account->primaryAccountNumber,
            account->cardHolderName,
            account->cardExpirationDate);

    fclose(file);
    return SERVER_OK;
}


EN_serverError_t updateAccountToFile(ST_accountsDB_t *account, const uint8 *filename)
{
    FILE *file = fopen(filename, "w");  // Open file in write mode to overwrite the file
    if (file == NULL)
    {
        perror("Error opening file");
        return SAVING_FAILED;
    }

    ST_accountsDB_t *current = account;

    while (current != NULL)
    {
        // Save account information in a comma-separated format
        fprintf(file, "%.2f,%d,%s,%s,%s\n",
                current->balance,
                current->state,
                current->primaryAccountNumber,
                current->cardHolderName,
                current->cardExpirationDate);

        current = current->next;  // Move to the next account in the linked list
    }

    fclose(file);
    return SERVER_OK;
}


EN_serverError_t loadAccountsFromFile(ST_accountsDB_t **head, const uint8 *filename)
{
    FILE *file = fopen(filename, "r");  // Open file in read mode
    if (file == NULL)
    {
        perror("Error opening file");
        return ACCOUNT_NOT_FOUND;
    }

    ST_accountsDB_t *newAccount;
    float32 balance;
    uint32 state;
    uint8 pan[20];
    uint8 cardHolderName[25];
    uint8 cardExpirationDate[6];

    // Read account data from the file using comma as a separator
    while (fscanf(file, "%f,%d,%[^,],%[^,],%s", &balance, &state, pan, cardHolderName, cardExpirationDate) == 5)
    {
        newAccount = (ST_accountsDB_t *)malloc(sizeof(ST_accountsDB_t));
        if (newAccount == NULL)
        {
            perror("Error allocating memory for new account");
            fclose(file);
            return SAVING_FAILED;
        }

        newAccount->balance = balance;
        newAccount->state = (EN_accountState_t)state;
        strcpy((uint8 *)newAccount->primaryAccountNumber, pan);
        strcpy((uint8 *)newAccount->cardHolderName, cardHolderName);
        strcpy((uint8 *)newAccount->cardExpirationDate, cardExpirationDate);

        newAccount->next = *head;  // Insert the new account at the beginning of the linked list
        *head = newAccount;
    }

    fclose(file);
    return SERVER_OK;
}

