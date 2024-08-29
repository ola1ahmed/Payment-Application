/*
---------------------------------------------------------------------------------------------------
Name:save_data
Parameters:No parameters
Return: Nothing to return
Usage: it used to save data after all function done (after changes in memory,to update csv file).
----------------------------------------------------------------------------------------------------
*/
void save_data()
 {
    FILE *file = fopen("database.csv", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fclose(file);

    HELP2 = Head;
    while (HELP2 != NULL) {
        file = fopen("database.csv", "a");
        if (file == NULL)
		{
            printf("Error opening file.\n");
            exit(1);
        }

        //fprintf(file, "%s,%f,%d,%s,%d,%s\n", HELP2->Name, HELP2->Grade, HELP2->Id, HELP2->Gender,HELP2->Age, HELP2->Password);
        //HELP2 = HELP2->NEXT;
        fclose(file);
    }
}

/*
----------------------------------------------------------------------------
Name:clear_list
Parameters:No parameters
Return: Nothing to return
Usage: it used to free memory(linked list space).
----------------------------------------------------------------------------
*/
void clear_list()
 {
    while (Head != NULL)
        {
        struct STUDENTS *ptr = Head;
        Head = Head->NEXT;
        free(ptr);
        }
 }
/*
----------------------------------------------------------------------------
Name:load_data
Parameters:No parameters
Return: Nothing to return
Usage: it used to load data at the beginning of program.
----------------------------------------------------------------------------
*/
void load_data(){
	flagg=0;
    clear_list();
    FILE *file = fopen("database.csv", "r");
    if (file == NULL)
        {
			printf("Error opening file.\n");
			exit(1);
        }
    char line[200];
    while (fgets(line, sizeof(line), file)) 
	{
        /*struct STUDENTS *newStudent = (struct STUDENTS *)malloc(sizeof(struct STUDENTS));
        if (newStudent == NULL) 
		{
            printf("Memory allocation failed.\n");
            exit(1);
        }

        sscanf(line, "%99[^,],%f,%d,%99[^,],%d,%s\n", newStudent->Name, &newStudent->Grade, &newStudent->Id, newStudent->Gender,&newStudent->Age, newStudent->Password);

        newStudent->NEXT = NULL;
        if(flagg++==0) Head = newStudent;
		else
		{
			HELP2=Head;
			while(HELP2->NEXT!=NULL) HELP2=HELP2->NEXT;
			HELP2->NEXT=newStudent;
		}*/
    }
    fclose(file);
}