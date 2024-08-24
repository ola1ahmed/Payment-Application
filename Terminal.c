#include "Terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
	
	EN_terminalError_t Ter_Err_state=TERMINAL_OK;
	uint8 transactionDate[11]={0};
	if(termData!=NULL)
	{
		
		
		printf("enter Transaction date:");
		gets(transactionDate);
		uint8 TransactionDateLength = strlen(transactionDate);

		if( (TransactionDateLength < 10) || (TransactionDateLength > 10) ||(transactionDate[2] != '/' || transactionDate[5] != '/') )
		{
			Ter_Err_state = WRONG_DATE;
		}
		else
		{
			strcpy(termData->transactionDate, transactionDate);
		}
	}
	else
	{
		Ter_Err_state=WRONG_DATE;
	}
	
	return Ter_Err_state;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t* termData){
	EN_terminalError_t Ter_Err_state=TERMINAL_OK;
	if((termData!=NULL) && (cardData!=NULL))
	{
		//"DD/MM/YYYY"
		
        uint8 transactionMonth = ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
        uint8 transactionYear = ((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0');
		

        // "MM/YY"
        uint8 cardExpirationMonth = ((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0');
        uint8 cardExpirationYear = ((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0');        

        if (transactionYear > cardExpirationYear) 
		{
            Ter_Err_state = EXPIRED_CARD;
        } 
		else if (transactionYear == cardExpirationYear) 
		{
            if (transactionMonth >= cardExpirationMonth) 
			{
                Ter_Err_state = EXPIRED_CARD;
            }
        }
	}
	else
	{
		Ter_Err_state=EXPIRED_CARD;
	}
	
	return Ter_Err_state;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
	
	EN_terminalError_t Ter_Err_state=TERMINAL_OK;
	if(termData!=NULL){
		
		
	}
	else
	{
		Ter_Err_state=WRONG_DATE;
	}
	
	return Ter_Err_state;
	
}
/*
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
	
	EN_terminalError_t Ter_Err_state=TERMINAL_OK;
	if(termData!=NULL){
		
		
	}
	else
	{
		Ter_Err_state=WRONG_DATE;
	}
	
	return Ter_Err_state;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float32 maxAmount){
	
	EN_terminalError_t Ter_Err_state=TERMINAL_OK;
	if(termData!=NULL){
		
		
	}
	else
	{
		Ter_Err_state=WRONG_DATE;
	}
	
	return Ter_Err_state;
}
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
	
	EN_terminalError_t Ter_Err_state=TERMINAL_OK;
	if(termData!=NULL){
		
		
	}
	else
	{
		Ter_Err_state=WRONG_DATE;
	}
	
	return Ter_Err_state;
}

*/

/*
--------------------------------------------------------------------------------

								privite TEST FUNCTION

--------------------------------------------------------------------------------
*/
static void getTransactionDateTest(void){
	
	
	ST_terminalData_t termData;
	EN_terminalError_t Ter_Err_state;
	
	
	printf("\nTest Case 1:\n");
	printf("Terminal Input Data:24/08/2024\n");
	Ter_Err_state=getTransactionDate(&termData);
	printf(" Expected Result:TERMINAL_OK\n");
	if(Ter_Err_state==WRONG_DATE)
	{
		printf(" Actual Result:WRONG_DATE \n");
	}
	else
	{
		printf(" Actual Result:TERMINAL_OK \n");
	}
	
	printf("\nTest Case 2:\n");
	printf("Terminal Input Data:24-08-2024\n");
	Ter_Err_state=getTransactionDate(&termData);
	printf(" Expected Result:WRONG_DATE\n");
	if(Ter_Err_state==WRONG_DATE)
	{
		printf(" Actual Result:WRONG_DATE \n");
	}
	else
	{
		printf(" Actual Result:TERMINAL_OK \n");
	}
	
	
	printf("\nTest Case 3:\n");

	printf("Terminal Input Data:2489024\n");
	Ter_Err_state=getTransactionDate(&termData);
	printf(" Expected Result:WRONG_DATE\n");
	if(Ter_Err_state==WRONG_DATE)
	{
		printf(" Actual Result:WRONG_DATE \n");
	}
	else
	{
		printf(" Actual Result:TERMINAL_OK \n");
	}
	
	
	
}
static void isCardExpriedTest(void){
	
	ST_cardData_t cardData;
	EN_cardError_t Card_stutes;
	
	ST_terminalData_t termData;
	EN_terminalError_t Ter_Err_state;
	
	
	printf("\n Test Case 1:\n");
	printf("Card Input Data:10/25\n");
	Card_stutes=getCardExpiryDate(&cardData);
	printf("Terminal Input Data:24/08/2024\n");
	getTransactionDate(&termData);
	Ter_Err_state=isCardExpired(&cardData,&termData);
	printf(" Expected Result:TERMINAL_OK\n");
	if(Ter_Err_state==EXPIRED_CARD)
	{
		printf(" Actual Result:EXPIRED_CARD \n");
	}
	else
	{
		printf(" Actual Result:TERMINAL_OK \n");
	}
	printf("\n Test Case 2:\n");
	printf("Card Input Data:02/24\n");
	Card_stutes=getCardExpiryDate(&cardData);
	printf("Terminal Input Data:24/08/2024\n");
	getTransactionDate(&termData);
	Ter_Err_state=isCardExpired(&cardData,&termData);
	printf(" Expected Result:EXPIRED_CARD\n");
	if(Ter_Err_state==EXPIRED_CARD)
	{
		printf(" Actual Result:EXPIRED_CARD \n");
	}
	else
	{
		printf(" Actual Result:TERMINAL_OK \n");
	}
	
	
	printf("\n Test Case 3:\n");
	printf("Card Input Data:02/23\n");
	Card_stutes=getCardExpiryDate(&cardData);
	printf("Terminal Input Data:24/08/2024\n");
	getTransactionDate(&termData);
	Ter_Err_state=isCardExpired(&cardData,&termData);
	printf(" Expected Result:EXPIRED_CARD\n");
	if(Ter_Err_state==EXPIRED_CARD)
	{
		printf(" Actual Result:EXPIRED_CARD \n");
	}
	else
	{
		printf(" Actual Result:TERMINAL_OK \n");
	}
}
static void getTransactionAmountTest(void){
	
	
}
static void isBelowMaxAmountTest(void){
	
	
}
static void setMaxAmountTest(void){
	
	
}
static void isValidCardPANTest(void){
	
	
}


