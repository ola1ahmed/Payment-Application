#include "Terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
	
	EN_terminalError_t Ter_Err_state=TERMINAL_OK;
	uint8 transactionDate[11]={0};
	if(termData!=NULL)
	{

		#if (MODULE == USER)
			printf("enter Transaction date(DD/MM/YYYY):");
			gets(transactionDate);
		#elif (MODULE ==TEST)
			strcpy(transactionDate,termData->transactionDate);
		#endif
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
	float32 transaction_amount;
	if(termData!=NULL)
	{
		
		#if (MODULE ==USER)
		printf("enter  transaction amount:");
		scanf("%f",&transaction_amount);
		#elif (MODULE ==TEST)
			transaction_amount=termData->transAmount;
		#endif

		if( (transaction_amount)<=0 )
		{
			Ter_Err_state = INVALID_AMOUNT;
		}
		else
		{
			termData->transAmount=transaction_amount;
			Ter_Err_state = TERMINAL_OK;
		}
		
	}
	else
	{
		Ter_Err_state=INVALID_AMOUNT;
	}
	
	return Ter_Err_state;
	
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
	
	EN_terminalError_t Ter_Err_state=TERMINAL_OK;
	if(termData!=NULL)
	{
		if( (termData->maxTransAmount) < (termData->transAmount) )
		{
			Ter_Err_state=EXCEED_MAX_AMOUNT;
		}
		else
		{
			Ter_Err_state=TERMINAL_OK;
		}
		
	}
	else
	{
		Ter_Err_state=WRONG_DATE;
	}
	
	return Ter_Err_state;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float32 maxAmount){
	
	EN_terminalError_t Ter_Err_state=TERMINAL_OK;
	if(termData!=NULL)
	{

		if( (maxAmount)<=0 )
		{
			Ter_Err_state = INVALID_MAX_AMOUNT;
		}
		else
		{
			termData->maxTransAmount=maxAmount;
			Ter_Err_state = TERMINAL_OK;
		}
		
	}
	else
	{
		Ter_Err_state=INVALID_MAX_AMOUNT;
	}
	
	return Ter_Err_state;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
	
	EN_terminalError_t Ter_Err_state=TERMINAL_OK;
	uint8 length=strlen(cardData->primaryAccountNumber);
	sint8 digit=0,i=0,sum=0;
	uint8 parity=length%2;
	
	if(cardData!=NULL)
	{
		for(i=length-1;i>=0;i--)
		{
			if(!isdigit(cardData->primaryAccountNumber[i]))
			{
				Ter_Err_state=INVALID_CARD;
				break;
			}
			digit=cardData->primaryAccountNumber[i]-'0';
			if(i%2==parity)
			{
				digit*=2;
				if(digit>9)
				{
					digit-=9;
				}
			}
			sum+=digit;
		}
		if(sum%10==0)
		{
			Ter_Err_state=TERMINAL_OK;
		}
		else
		{
			Ter_Err_state=INVALID_CARD;
		}
		
	}
	else
	{
		Ter_Err_state=WRONG_DATE;
	}
	
	return Ter_Err_state;
}



/*
--------------------------------------------------------------------------------

								 TEST FUNCTION

--------------------------------------------------------------------------------
*/

#if (MODULE==TEST)
void getTransactionDateTest(void) {
    ST_terminalData_t termData;
    EN_terminalError_t Ter_Err_state;
	
    printf("--------------------------------------------------------------------------------------------\n");
	printf("\t\t\tgetTransactionDateTest\t\t\t\n");
    // Test Case 1: Valid Date Format
    printf("\nTest Case 1:\n");
    printf("Terminal Input Data: 24/08/2024\n");
    strcpy( (char *)termData.transactionDate, "24/08/2024");  
    Ter_Err_state = getTransactionDate(&termData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", Ter_Err_state == TERMINAL_OK ? "TERMINAL_OK" : "WRONG_DATE");
    
    // Test Case 2: Invalid Date Format with dashes
    printf("\nTest Case 2:\n");
    printf("Terminal Input Data: 24-08-2024\n");
    strcpy((char *)termData.transactionDate, "24-08-2024");  
    Ter_Err_state = getTransactionDate(&termData);
    printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result: %s\n", Ter_Err_state == TERMINAL_OK ? "TERMINAL_OK" : "WRONG_DATE");
    
    // Test Case 3: Invalid Date Format, incorrect length
    printf("\nTest Case 3:\n");
    printf("Terminal Input Data: 2489024\n");
    strcpy((char *)termData.transactionDate, "2489024");  
    Ter_Err_state = getTransactionDate(&termData);
    printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result: %s\n", Ter_Err_state == TERMINAL_OK ? "TERMINAL_OK" : "WRONG_DATE");
}


	
void isCardExpiredTest(void) {
    ST_cardData_t cardData;
    ST_terminalData_t termData;
    EN_terminalError_t Ter_Err_state;

	printf("--------------------------------------------------------------------------------------------\n");
	printf("\t\t\tisCardExpiredTest\t\t\t\n");
    // Test Case 1: Card Not Expired
    printf("\nTest Case 1:\n");
    printf("Card Expiry Date: 10/25\n");
    strcpy((char *)cardData.cardExpirationDate, "10/25");  
    printf("Transaction Date: 24/08/2024\n");
    strcpy((char *)termData.transactionDate, "24/08/2024");  
    Ter_Err_state = isCardExpired(&cardData, &termData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", Ter_Err_state == TERMINAL_OK ? "TERMINAL_OK" : "EXPIRED_CARD");

    // Test Case 2: Card Expired
    printf("\nTest Case 2:\n");
    printf("Card Expiry Date: 02/24\n");
    strcpy((char *)cardData.cardExpirationDate, "02/24");  
    printf("Transaction Date: 24/08/2024\n");
    strcpy((char *)termData.transactionDate, "24/08/2024");  
    Ter_Err_state = isCardExpired(&cardData, &termData);
    printf("Expected Result: EXPIRED_CARD\n");
    printf("Actual Result: %s\n", Ter_Err_state == TERMINAL_OK ? "TERMINAL_OK" : "EXPIRED_CARD");
    
    // Test Case 3: Card Expired (more past date)
    printf("\nTest Case 3:\n");
    printf("Card Expiry Date: 02/23\n");
    strcpy((char *)cardData.cardExpirationDate, "02/23");  
    printf("Transaction Date: 24/08/2024\n");
    strcpy((char *)termData.transactionDate, "24/08/2024");  
    Ter_Err_state = isCardExpired(&cardData, &termData);
    printf("Expected Result: EXPIRED_CARD\n");
    printf("Actual Result: %s\n", Ter_Err_state == TERMINAL_OK ? "TERMINAL_OK" : "EXPIRED_CARD");
}

void getTransactionAmountTest(void) 
{
    ST_terminalData_t termData;
    EN_terminalError_t Ter_Err_state;
    
	printf("--------------------------------------------------------------------------------------------\n");
	printf("\t\t\tgetTransactionAmountTest\t\t\t\n");
    // Test Case 1: Negative Amount
    printf("\nTest Case 1:\n");
    printf("Transaction Amount: -100\n");
    termData.transAmount = -100;  
    Ter_Err_state = getTransactionAmount(&termData);
    printf("Expected Result: INVALID_AMOUNT\n");
    printf("Actual Result: %s\n", Ter_Err_state == INVALID_AMOUNT ? "INVALID_AMOUNT" : "TERMINAL_OK");
    
    // Test Case 2: Zero Amount
    printf("\nTest Case 2:\n");
    printf("Transaction Amount: 0\n");
    termData.transAmount = 0;  
    Ter_Err_state = getTransactionAmount(&termData);
    printf("Expected Result: INVALID_AMOUNT\n");
    printf("Actual Result: %s\n", Ter_Err_state == INVALID_AMOUNT ? "INVALID_AMOUNT" : "TERMINAL_OK");
    
    // Test Case 3: Valid Amount
    printf("\nTest Case 3:\n");
    printf("Transaction Amount: 100\n");
    termData.transAmount = 100;  
    Ter_Err_state = getTransactionAmount(&termData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", Ter_Err_state == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_AMOUNT");
}


void isBelowMaxAmountTest(void) 
{
    ST_terminalData_t termData;
    EN_terminalError_t Ter_Err_state;
    
	printf("--------------------------------------------------------------------------------------------\n");
	printf("\t\t\tisBelowMaxAmountTest\t\t\t\n");
    // Test Case 1: Transaction Amount Exceeds Max Amount
    printf("\nTest Case 1:\n");
    printf("Max Amount: 90\n");
    printf("Transaction Amount: 100\n");
    termData.transAmount = 100;  
    termData.maxTransAmount = 90;  
    Ter_Err_state = isBelowMaxAmount(&termData);
    printf("Expected Result: EXCEED_MAX_AMOUNT\n");
    printf("Actual Result: %s\n", Ter_Err_state == EXCEED_MAX_AMOUNT ? "EXCEED_MAX_AMOUNT" : "TERMINAL_OK");
    
    // Test Case 2: Transaction Amount is Below Max Amount
    printf("\nTest Case 2:\n");
    printf("Max Amount: 120\n");
    printf("Transaction Amount: 100\n");
    termData.transAmount = 100;  
    termData.maxTransAmount = 120;  
    Ter_Err_state = isBelowMaxAmount(&termData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", Ter_Err_state == EXCEED_MAX_AMOUNT ? "EXCEED_MAX_AMOUNT" : "TERMINAL_OK");
}

void setMaxAmountTest(void) {
	
    ST_terminalData_t termData;
    EN_terminalError_t Ter_Err_state;
    
	printf("--------------------------------------------------------------------------------------------\n");
	printf("\t\t\tsetMaxAmountTest\t\t\t\n");
    // Test Case 1: Max Amount is Zero
    printf("\nTest Case 1:\n");
    printf("Max Amount: 0\n");
    Ter_Err_state = setMaxAmount(&termData, 0);
    printf("Expected Result: INVALID_MAX_AMOUNT\n");
    printf("Actual Result: %s\n", Ter_Err_state == INVALID_MAX_AMOUNT ? "INVALID_MAX_AMOUNT" : "TERMINAL_OK");
    
    // Test Case 2: Valid Max Amount
    printf("\nTest Case 2:\n");
    printf("Max Amount: 1000\n");
    Ter_Err_state = setMaxAmount(&termData, 1000);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", Ter_Err_state == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_MAX_AMOUNT");
}

void isValidCardPANTest(void) {
    ST_cardData_t cardData;
    EN_terminalError_t result;

	printf("--------------------------------------------------------------------------------------------\n");
	printf("\t\t\tisValidCardPANTest\t\t\t\n");
    // Test Case 1: Valid Luhn number
	
    strcpy((char *)cardData.primaryAccountNumber, "4532015112830366");  
    result = isValidCardPAN(&cardData);
    printf("Test Case 1: Input PAN: %s\n", cardData.primaryAccountNumber);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n\n", result == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_CARD");

    // Test Case 2: Invalid Luhn number
    strcpy((char *)cardData.primaryAccountNumber, "1234567890123456");  
    result = isValidCardPAN(&cardData);
    printf("Test Case 2: Input PAN: %s\n", cardData.primaryAccountNumber);
    printf("Expected Result: INVALID_CARD\n");
    printf("Actual Result: %s\n\n", result == INVALID_CARD ? "INVALID_CARD" : "TERMINAL_OK");

    // Test Case 3: PAN with non-digit characters
    strcpy((char *)cardData.primaryAccountNumber, "4532a05112830366");  
    result = isValidCardPAN(&cardData);
    printf("Test Case 3: Input PAN: %s\n", cardData.primaryAccountNumber);
    printf("Expected Result: INVALID_CARD\n");
    printf("Actual Result: %s\n\n", result == INVALID_CARD ? "INVALID_CARD" : "TERMINAL_OK");

    // Test Case 4: PAN with correct length but invalid Luhn sum
    strcpy((char *)cardData.primaryAccountNumber, "4532015112830360");  
    result = isValidCardPAN(&cardData);
    printf("Test Case 4: Input PAN: %s\n", cardData.primaryAccountNumber);
    printf("Expected Result: INVALID_CARD\n");
    printf("Actual Result: %s\n\n", result == INVALID_CARD ? "INVALID_CARD" : "TERMINAL_OK");
}


#endif


