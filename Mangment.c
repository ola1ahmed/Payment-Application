#include "Mangement.h"

/*
----------------------------------------------------------------------------
Name:clearScreen
Parameters:No parameters
Return: Nothing to return
Usage: it used to clear screen after each process.
----------------------------------------------------------------------------
*/

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

}
/*
----------------------------------------------------------------------------
Name:EXIT
Parameters:No parameters
Return: Nothing to return
Usage: it used to exit out of program.
----------------------------------------------------------------------------
*/
void EXIT(){
    printf("loading");
    for(int i=0;i<3;i++)
        {
            printf(".");
            sleep(1);
        }
    clearScreen();
    printf("thank you <3 \n");
}