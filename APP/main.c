
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


/*
gcc -o my_program APP/main.c APP/app.c CARD/Card.c TERMINAL/Terminal.c Server/server.c Data_Structure/linkedlist.c Data_Structure/stack.c Data_Structure/queue.c FILE_HANDLING/File_handling.c
my_program.exe
*/