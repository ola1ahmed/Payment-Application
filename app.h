
#ifndef _APP_H_
#define _APP_H_


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>

#include "server.h"
#include "queue.h"
#include "stack.h"
#include "linkedlist.h"
#include "file_handling.h" 
#include "Terminal.h"
#include "Card.h"
/*
--------------------------------------------------------------------------------

								public FUNCTION

--------------------------------------------------------------------------------
*/
void Login(void);
void firstpage(void);
void appStart(void);
void clearScreen();
void EXIT();
/*
--------------------------------------------------------------------------------

								 TEST FUNCTION

--------------------------------------------------------------------------------
*/

void addTestTransactions(void);
void testApplication(void);


#endif