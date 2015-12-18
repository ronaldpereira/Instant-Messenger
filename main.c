#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"

int main()
{
	TBList *TBList; // Creates a big list and a pointer to the big list created
	createBList(&TBList); // Calls the function to do a malloc for the big list using the pointer
	readInput(TBList); // Call the function that reads the input and calls the rest of the functions to do the rest
	freeBLists(TBList); // Call the function that free all the big lists created and used in the program execution
	free(TBList); // Do a free in the first created big list
	return 0;
}
