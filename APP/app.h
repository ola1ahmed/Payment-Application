
#ifndef _APP_H_
#define _APP_H_


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>



#include "../Server/server.h"
#include "../CARD/Card.h"
#include "../TERMINAL/Terminal.h"


void Login(void);
/*
----------------------------------------------------------------------------
Name:Login
Parameters:No parameters
Return: Nothing to return
Usage: it used to open login page.
----------------------------------------------------------------------------
*/
void firstpage(void);
/*
----------------------------------------------------------------------------
Name:clearScreen
Parameters:No parameters
Return: Nothing to return
Usage: it used to open first page.
----------------------------------------------------------------------------
*/
void appStart(void);
/*
----------------------------------------------------------------------------
Name:clearScreen
Parameters:No parameters
Return: Nothing to return
Usage: it used to clear screen after each process.
----------------------------------------------------------------------------
*/
void clearScreen();
/*
----------------------------------------------------------------------------
Name:EXIT
Parameters:No parameters
Return: Nothing to return
Usage: it used to exit out of program &free memory allocation.
----------------------------------------------------------------------------
*/
void EXIT();



/*
--------------------------------------------------------------------------------

								 TEST FUNCTION

--------------------------------------------------------------------------------
*/

void testApplication(void);


#endif