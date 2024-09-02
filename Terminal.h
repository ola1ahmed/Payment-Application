#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "Card.h"




typedef struct ST_terminalData_t
{
	float32 transAmount;
	float32 maxTransAmount;
	uint8 transactionDate[11];
	
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
	TERMINAL_OK,
	WRONG_DATE,
	EXPIRED_CARD,
	INVALID_CARD,
	INVALID_AMOUNT,
	EXCEED_MAX_AMOUNT,
	INVALID_MAX_AMOUNT
}EN_terminalError_t ;
/*
--------------------------------------------------------------------------------

								public FUNCTION

--------------------------------------------------------------------------------
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t* termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float32 maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);
/*
--------------------------------------------------------------------------------

								privite TEST FUNCTION

--------------------------------------------------------------------------------
*/
void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isValidCardPANTest(void);
#endif