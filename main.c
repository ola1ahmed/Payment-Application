#include "app.h"
#include <stdio.h>
#include <stdlib.h>


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