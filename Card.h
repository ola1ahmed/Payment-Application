#ifndef _CARD_H_
#define _CARD_H_

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "STD_TYPES.h"

typedef struct ST_cardData_t
{
 uint8 cardHolderName[25];
 uint8 primaryAccountNumber[20];
 uint8 cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
 CARD_OK,
 WRONG_NAME,
 WRONG_EXP_DATE,
 WRONG_PAN
}EN_cardError_t;
/*
--------------------------------------------------------------------------------

								public FUNCTION

--------------------------------------------------------------------------------
*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
/*
--------------------------------------------------------------------------------

								privite TEST FUNCTION

--------------------------------------------------------------------------------
*/
static void getCardHolderNameTest(void);
static void getCardExpiryDateTest (void);
static void getCardPANTest(void); 


#endif