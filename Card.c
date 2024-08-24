#include "Card.h"


EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	EN_cardError_t Card_Err_state=CARD_OK;
	uint8 CardHolderName[25]={0};
	uint8 CardHolderName_len;
	
	if(cardData!=NULL)
	{
		printf("enter cardholder's name:");
		gets(CardHolderName);
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
		
		printf("enter card expiry date:");
		gets(cardExpirationDate);
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
		printf("enter Primary Account Number:");
		gets(primaryAccountNumber);
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
static void getCardHolderNameTest(void){
	
	ST_cardData_t cardData;
	EN_cardError_t stutes;
	
	
	printf("\n Test Case 1:\n");
	printf("Input Data:ola ahmed mobark\n");
	stutes=getCardHolderName(&cardData);
	printf(" Expected Result:WRONG_NAME\n");
	if(stutes==WRONG_NAME)
	{
		printf(" Actual Result:WRONG_NAME \n");
	}
	else
	{
		printf(" Actual Result:CARD_OK \n");
	}
	
	
	
	printf("\n Test Case 2:\n");
	printf("Input Data: ola ahmed el_hossiny mo\n");
	stutes=getCardHolderName(&cardData);
	printf(" Expected Result:CARD_OK\n");
	if(stutes==WRONG_NAME)
	{
		printf(" Actual Result:WRONG_NAME \n");
	}
	else
	{
		printf(" Actual Result:CARD_OK \n");
	}
	
}
static void getCardExpiryDateTest (void)
{
	
	ST_cardData_t cardData;
	EN_cardError_t stutes;
	
	
	printf("\n Test Case 1:\n");
	printf("Input Data:1010\n");
	stutes=getCardExpiryDate(&cardData);
	printf(" Expected Result:WRONG_EXP_DATE\n");
	if(stutes==WRONG_EXP_DATE)
	{
		printf(" Actual Result:WRONG_EXP_DATE \n");
	}
	else
	{
		printf(" Actual Result:CARD_OK \n");
	}
	
	
	
	printf("\n Test Case 2:\n");
	printf("Input Data:10/24\n");
	stutes=getCardExpiryDate(&cardData);
	printf(" Expected Result:CARD_OK\n");
	if(stutes==WRONG_EXP_DATE)
	{
		printf(" Actual Result:WRONG_EXP_DATE \n");
	}
	else
	{
		printf(" Actual Result:CARD_OK \n");
	}
}
static void getCardPANTest(void){
	
	
	ST_cardData_t cardData;
	EN_cardError_t stutes;
	
	
	printf("\n Test Case 1:\n");
	printf("Input Data:1234\n");
	stutes=getCardPAN(&cardData);
	printf(" Expected Result:WRONG_PAN\n");
	if(stutes==WRONG_PAN)
	{
		printf(" Actual Result:WRONG_PAN \n");
	}
	else
	{
		printf(" Actual Result:CARD_OK \n");
	}
	printf("\n Test Case 2:\n");
	printf("Input Data:qwertyuioasdfghjkl\n");
	stutes=getCardPAN(&cardData);
	printf(" Expected Result:WRONG_PAN\n");
	if(stutes==WRONG_PAN)
	{
		printf(" Actual Result:WRONG_PAN \n");
	}
	else
	{
		printf(" Actual Result:CARD_OK \n");
	}
	
	
	printf("\n Test Case 3:\n");
	printf("Input Data:12345678910111213\n");
	stutes=getCardPAN(&cardData);
	printf(" Expected Result:CARD_OK\n");
	if(stutes==WRONG_PAN)
	{
		printf(" Actual Result:WRONG_PAN \n");
	}
	else
	{
		printf(" Actual Result:CARD_OK \n");
	}	
	
}
