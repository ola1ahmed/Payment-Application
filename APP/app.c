#include "app.h"


TransactionQueue *transactionsDB = NULL;  
status_t status;
stutes_t stackstutes;
TransactionStack *stack= {NULL};

ST_accountsDB_t *accountsDB = NULL;  
extern const uint8 *accountsFilename;
extern const uint8 *transactionFilename ;
uint32 lastSequenceNumber ;

extern ST_accountsDB_t *accountReference;
#if (MODULE==USER)
void Login(void){
	uint8 choise;
	sint8 flag=-1;
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
	
	while(flag==-1)
	{
		flag=0;
		printf("******************************************************\n");
		printf("for LOGIN enter [L] : \n");
		printf("for EXIT  enter [E] : \n");
		printf("******************************************************\n");
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
			case 'l':
			case 'L':
				firstpage();
				break;
			case 'e':
			case 'E':
				EXIT();
				return;
			default:
				flag=-1;
				printf("invalid option\n");
				sleep(1);

				break;
		}
	
	}
}
void firstpage(void){
	uint8 choise;
	while(1)
	{
		printf("******************************************************\n");
		printf("for Transactions enter				[T]:\n");
		printf("for List All Saved Transactions			[A]:\n");
		printf("for Last Saved Transactions			[L]:\n");
		printf("for EXIT enter					[E]:\n");
		printf("******************************************************\n");
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
				case 't':
				case 'T':
					appStart();
					break;
				case 'a':
				case 'A':
					listSavedTransactions();
					break;
				case 'l':
				case 'L':
					lastSavedTransactions();
					
					break;
				case 'e':
				case 'E':
					EXIT();
					return;		
				default:
					printf("invalid option\n");
					sleep(1);
					break;
			}
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
	cardError = isValidCardPAN(&cardData);
    if (cardError != TERMINAL_OK) 
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
   
    terminalError = setMaxAmount(&terminalData, 2000.0);
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
			
		case DECLINED_INSUFFECIENT_FUND: printf("DECLINED_INSUFFECIENT_FUND\n"); break;
		case DECLINED_STOLEN_CARD: printf("DECLINED_STOLEN_CARD\n"); break;
		case FRAUD_CARD: printf("FRAUD_CARD\n"); break;
		case INTERNAL_SERVER_ERROR: printf("INTERNAL_SERVER_ERROR\n"); break;
			
		}
        return;
    }

    printf("Transaction approved.\n");
	uint8 choise;
		printf("******************************************************\n");
		printf("for List All Transactions			[s]:\n");
		printf("for EXIT this page enter			[E]:\n");
		printf("******************************************************\n");
		fflush(stdin);
		scanf("%c",&choise);
		switch(choise)
		{
			case 's':
				spacific_account(transactionsDB,accountReference,print_Queue);
				break;
			case'e':
				EXIT();
				return;				
					
		}
}
#endif


void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

}

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
	
    recieveTransactionDataTest();
    listSavedTransactionsTest();
	
/*	EXIT();*/
}
#endif

