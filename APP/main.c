
#include <stdio.h>
#include <stdlib.h>

#include "app.h"

int main()
{
	#if (MODULE==USER)
    Login();
	#elif (MODULE==TEST)
    testApplication();
	#endif
    return 0;
}

//gcc main.c app.c Card.c Terminal.c Server.c File_handling.c linkedlist.c queue.c stack.c
//gcc -o my_program APP/main.c APP/app.c CARD/Card.c TERMINAL/Terminal.c Server/server.c Data_Structure/linkedlist.c Data_Structure/stack.c Data_Structure/queue.c FILE_HANDLING/File_handling.c
//my_program.exe
