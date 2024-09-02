#include "app.h"

TransactionQueue *transactionsDB = NULL;  
status_t status;
stutes_t stackstutes;
TransactionStack *stack= {NULL};

ST_accountsDB_t *accountsDB = NULL;  
extern const uint8 *accountsFilename;
extern const uint8 *transactionFilename ;
uint32 lastSequenceNumber ;

#if (MODULE==USER)
void Login(void){
	uint8 choise;
	loadAccountsFromFile(&accountsDB,accountsFilename);
	printAccounts(accountsDB);
	if (transactionsDB == NULL)
    {
		transactionsDB=Create_Queue(&status);
		stack=CreateStack(&stackstutes);
	}
	loadTransactionsFromFile(stack,transactionsDB,transactionFilename);
	if (transactionsDB->rear != NULL) 
	{
        lastSequenceNumber = transactionsDB->rear->transaction.transactionSequenceNumber;
    } 
	else 
	{
        lastSequenceNumber = 0; 
    }
	
	while(1)
	{
		printf("***************************\n");
		printf("for LOGIN enter [L] : \n");
		printf("for EXIT  enter [E] : \n");
		printf("***************************\n");
		fflush(stdin);
		scanf("%c",&choise);
		/*printf("loading");
		for(int i=0;i<3;i++)
			{
				printf(".");
				sleep(1);
			}
		clearScreen();*/
		switch(choise)
		{
		case 'L':
			firstpage();
			break;
		case 'E':
			EXIT();
			return;
		default:
			Login();
			break;
		}
	}
	
}
void firstpage(void){
	uint8 choise;
	printf("***************************\n");
	printf("for Transactions enter [T] : \n");
	printf("for listSavedTransactions [L]\n");
	printf("for EXIT  enter [E] : \n");
	printf("***************************\n");
	fflush(stdin);
		scanf("%c",&choise);
		/*printf("loading");
		for(int i=0;i<3;i++)
			{
				printf(".");
				sleep(1);
			}
		clearScreen();*/
		switch(choise)
		{
		case 'T':
			appStart();
			break;
		case 'L':
		listSavedTransactions();
		break;
		case 'E':
			EXIT();
			return;
		default:
			firstpage();
			break;
		}
	
	
}

void appStart(void) {
    ST_cardData_t cardData;
    ST_terminalData_t terminalData;
    ST_transaction_t transaction;
    EN_cardError_t cardError;
    EN_terminalError_t terminalError;
    EN_transStat_t transactionStatus;
	
	
	
	fflush(stdin);
    cardError = getCardHolderName(&cardData);
    if (cardError != CARD_OK) {
        printf("Error: Invalid card holder name.\n");
        return;
    }   
    cardError = getCardExpiryDate(&cardData);
    if (cardError != CARD_OK) {
        printf("Error: Invalid card expiry date.\n");
        return;
    }
    cardError = getCardPAN(&cardData);
    if (cardError != CARD_OK) 
	{
        printf("Error: Invalid card PAN.\n");
        return;
    }
    terminalError = getTransactionDate(&terminalData);
    if (terminalError != TERMINAL_OK) 
	{
        printf("Error: Invalid transaction date.\n");
        return;
    }
    terminalError = isCardExpired(&cardData, &terminalData);
    if (terminalError == EXPIRED_CARD) 
	{
        printf("Transaction declined: Expired card.\n");
        return;
    }
    terminalError = getTransactionAmount(&terminalData);
    if (terminalError != TERMINAL_OK) 
	{
        printf("Error: Invalid transaction amount.\n");
        return;
    }
   
    terminalError = setMaxAmount(&terminalData, 20000.0);
    if (terminalError != TERMINAL_OK) 
	{
        printf("Error: Invalid max amount.\n");
        return;
    }

    terminalError = isBelowMaxAmount(&terminalData);
    if (terminalError == EXCEED_MAX_AMOUNT) 
	{
        printf("Transaction declined: Amount exceeding limit.\n");
        return;
    }

    transaction.cardHolderData = cardData;
    transaction.terminalData = terminalData;
	
	transactionStatus = recieveTransactionData(&transaction);

    if (transactionStatus != APPROVED) 
	{
        printf("Transaction declined :");
		switch(transactionStatus)
		{
			
		case DECLINED_INSUFFECIENT_FUND: printf("DECLINED_INSUFFECIENT_FUND"); break;
		case DECLINED_STOLEN_CARD: printf("DECLINED_STOLEN_CARD\n"); break;
		case FRAUD_CARD: printf("FRAUD_CARD"); break;
		case INTERNAL_SERVER_ERROR: printf("INTERNAL_SERVER_ERROR"); break;
			
		}
        return;
    }

    printf("Transaction approved.\n");
}
#endif
/*
----------------------------------------------------------------------------
Name:clearScreen
Parameters:No parameters
Return: Nothing to return
Usage: it used to clear screen after each process.
----------------------------------------------------------------------------
*/

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

}
/*
----------------------------------------------------------------------------
Name:EXIT
Parameters:No parameters
Return: Nothing to return
Usage: it used to exit out of program &free memory allocation.
----------------------------------------------------------------------------
*/
void EXIT(){
	Destroy_Queue(transactionsDB);
	destroyStack(stack);
	destroylist(&accountsDB);
    printf("loading");
    for(int i=0;i<3;i++)
        {
            printf(".");
            sleep(1);
        }
    clearScreen();
    printf("thank you <3 \n");
}



#if (MODULE==TEST)

void addTestTransactions(void) {
    ST_transaction_t transaction1, transaction2;
    status_t status;

    // Set data for transaction 1
    transaction1.transactionSequenceNumber = lastSequenceNumber++;
    strcpy((char *)transaction1.terminalData.transactionDate, "12/12/2024");
    transaction1.terminalData.transAmount = 900.00;
    transaction1.terminalData.maxTransAmount = 1000.00;
    strcpy((char *)transaction1.cardHolderData.cardHolderName, "ola ahmed el_hossiny mo");
    strcpy((char *)transaction1.cardHolderData.primaryAccountNumber, "12345678901234567");
    strcpy((char *)transaction1.cardHolderData.cardExpirationDate, "12/24");
    transaction1.transState = APPROVED;

    // Set data for transaction 2
    transaction2.transactionSequenceNumber =lastSequenceNumber++;
    strcpy((char *)transaction2.terminalData.transactionDate, "13/12/2024");
    transaction2.terminalData.transAmount = 100.00;
    transaction2.terminalData.maxTransAmount = 1000.00;
    strcpy((char *)transaction2.cardHolderData.cardHolderName, "ahmed ahmed el_hossiny");
    strcpy((char *)transaction2.cardHolderData.primaryAccountNumber, "23456789012345678");
    strcpy((char *)transaction2.cardHolderData.cardExpirationDate, "01/25");
    transaction2.transState = DECLINED_INSUFFECIENT_FUND;

    // Enqueue transactions
    Enqueue_Element(transactionsDB, &transaction1);
    Enqueue_Element(transactionsDB, &transaction2);
}

void testApplication(void)
{
    
	loadAccountsFromFile(&accountsDB,accountsFilename);
	printAccounts(accountsDB);
	if (transactionsDB == NULL)
    {
		transactionsDB=Create_Queue(&status);
		stack=CreateStack(&stackstutes);
	}
	loadTransactionsFromFile(stack,transactionsDB,transactionFilename);
	if (transactionsDB->rear != NULL) 
	{
        lastSequenceNumber = transactionsDB->rear->transaction.transactionSequenceNumber;
    } 
	else 
	{
        lastSequenceNumber = 0; 
    }
	

/*
	getCardHolderNameTest();
	getCardExpiryDateTest ();
	getCardPANTest(); 
	
	getTransactionDateTest();
	isCardExpiredTest();
	getTransactionAmountTest();
	
	isBelowMaxAmountTest();
	setMaxAmountTest();
	isValidCardPANTest();
	
	
    isValidAccountTest();
    isBlockedAccountTest();
    isAmountAvailableTest();

	addTestTransactions();*/
    recieveTransactionDataTest();
    listSavedTransactionsTest();
	
/*	EXIT();*/
}
#endif

