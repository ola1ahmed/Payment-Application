
#include "Card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	EN_cardError_t Card_Err_state=CARD_OK;
	uint8 CardHolderName[25]={0};
	uint8 CardHolderName_len;
	
	if(cardData!=NULL)
	{
		
		#if (MODULE ==USER)
			printf("enter cardholder's name:");
			gets(CardHolderName);
		#elif (MODULE ==TEST)
			strcpy(CardHolderName,cardData->cardHolderName);
		#endif
		CardHolderName_len=strlen(CardHolderName);
		if((CardHolderName_len >20) && (CardHolderName_len<24))
		{
			strcpy(cardData->cardHolderName,CardHolderName);
			Card_Err_state=CARD_OK;
			
		}
		else
		{
			Card_Err_state=WRONG_NAME;
		}
		
	}
	else
	{
		Card_Err_state=WRONG_NAME;
	}
	return Card_Err_state;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
	EN_cardError_t Card_Err_state=CARD_OK;
	uint8 cardExpirationDate[6]={0};
	if(cardData!=NULL)
	{
		
		
		#if (MODULE ==USER)
			printf("enter card expiry date (MM/YY):");
			gets(cardExpirationDate);
		#elif (MODULE ==TEST)
			strcpy(cardExpirationDate,cardData->cardExpirationDate);
		#endif
		if(strlen(cardExpirationDate)!=5)
		{
			Card_Err_state=WRONG_EXP_DATE;
		}
		else if(cardExpirationDate[2]!='/')
		{
			Card_Err_state=WRONG_EXP_DATE;
		}
		else
		{
			strcpy(cardData->cardExpirationDate,cardExpirationDate);
			Card_Err_state=CARD_OK;
		}
		
	}
	else
	{
		Card_Err_state=WRONG_EXP_DATE ;
	}
	return Card_Err_state;


}
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
	EN_cardError_t Card_Err_state=CARD_OK;
	uint8 primaryAccountNumber[20]={0};
	uint8 counter=0;
	uint8 flag=0;
	if(cardData!=NULL)
	{
		
		#if (MODULE ==USER)
			printf("enter Primary Account Number:");
			gets(primaryAccountNumber);
		#elif (MODULE ==TEST)
			strcpy(primaryAccountNumber,cardData->primaryAccountNumber);
		#endif
		if((strlen(primaryAccountNumber)>16) &&(strlen(primaryAccountNumber)<19))
		{
			for(counter=0;counter<strlen(primaryAccountNumber);counter++)
			{	
				if(isdigit(primaryAccountNumber[counter])==0)
				{
					flag=1;
				}
			}
			if(flag!=1)
			{
				Card_Err_state=CARD_OK;
				strcpy(cardData->primaryAccountNumber,primaryAccountNumber);
			}
			else
			{
				Card_Err_state=WRONG_PAN;
			}
		}
		else 
		{
			Card_Err_state=WRONG_PAN;
		}
		
		
	}
	else
	{
		Card_Err_state=WRONG_PAN;
	}
	return Card_Err_state;
	
	
	
}
/*
--------------------------------------------------------------------------------

								TEST FUNCTION

--------------------------------------------------------------------------------
*/
#if (MODULE == TEST)


 void getCardHolderNameTest(void) {
    ST_cardData_t cardData;
    EN_cardError_t result;

    printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\t\tgetCardHolderNameTest\t\t\t\n");

    
    printf("\nTest Case 1:\n");
    printf("Input Data: ola ahmed mobark\n");
    strcpy((char *)cardData.cardHolderName, "ola ahmed mobark");
    result = getCardHolderName(&cardData);
    printf("Expected Result: WRONG_NAME\n");
    printf("Actual Result: %s\n", result == WRONG_NAME ? "WRONG_NAME" : "CARD_OK");

    
    printf("\nTest Case 2:\n");
    printf("Input Data: ola ahmed el_hossiny mo\n");
    strcpy((char *)cardData.cardHolderName, "ola ahmed el_hossiny mo");
    result = getCardHolderName(&cardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_NAME");
}


 void getCardExpiryDateTest(void) {
    ST_cardData_t cardData;
    EN_cardError_t result;

    printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\t\tgetCardExpiryDateTest\t\t\t\n");

   
    printf("\nTest Case 1:\n");
    printf("Input Data: 1010\n");
    strcpy((char *)cardData.cardExpirationDate, "1010");
    result = getCardExpiryDate(&cardData);
    printf("Expected Result: WRONG_EXP_DATE\n");
    printf("Actual Result: %s\n", result == WRONG_EXP_DATE ? "WRONG_EXP_DATE" : "CARD_OK");

    
    printf("\nTest Case 2:\n");
    printf("Input Data: 10/24\n");
    strcpy((char *)cardData.cardExpirationDate, "10/24");
    result = getCardExpiryDate(&cardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_EXP_DATE");
}


 void getCardPANTest(void) {
    ST_cardData_t cardData;
    EN_cardError_t result;

    printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\t\tgetCardPANTest\t\t\t\n");

    
    printf("\nTest Case 1:\n");
    printf("Input Data: 1234\n");
    strcpy((char *)cardData.primaryAccountNumber, "1234");
    result = getCardPAN(&cardData);
    printf("Expected Result: WRONG_PAN\n");
    printf("Actual Result: %s\n", result == WRONG_PAN ? "WRONG_PAN" : "CARD_OK");

   
    printf("\nTest Case 2:\n");
    printf("Input Data: qwertyuioasdfghjkl\n");
    strcpy((char *)cardData.primaryAccountNumber, "qwertyuioasdfghjkl");
    result = getCardPAN(&cardData);
    printf("Expected Result: WRONG_PAN\n");
    printf("Actual Result: %s\n", result == WRONG_PAN ? "WRONG_PAN" : "CARD_OK");

   
    printf("\nTest Case 3:\n");
    printf("Input Data: 12345678910111213\n");
    strcpy((char *)cardData.primaryAccountNumber, "12345678910111213");
    result = getCardPAN(&cardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_PAN");
}

#endif


