#ifndef _CARD_H_
#define _CARD_H_

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../Library/STD_TYPES.h"

#include "../Data_Structure/linkedlist.h"
#include "../Data_Structure/queue.h"
#include "../Data_Structure/stack.h"

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
void getCardHolderNameTest(void);
void getCardExpiryDateTest (void);
void getCardPANTest(void); 


#endif