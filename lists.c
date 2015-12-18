#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"
#define MAX 10000


void incrementK (TBList *List) // Increment the "K" in 1 each time 
{
	Apontador p;
	
	for (p = List->Primeiro->Prox; p != NULL; p = p->Prox)
	{
		p->Inactive++;
	}
}

int checkTBList (TBCell *List) // Checks if the Little list is empty, and returns 1 if it's true, 0 if it's false
{
	return (List->First == List->Last);
}

void freeLLists (TBCell *List) // Free the little list on the memory
{
    Pointer p;
     
    for (p=List->First; p != NULL; p = p->Next)
    {
        free(p);
    }
}

void freeK (TBList *List, int k, int *v) // Free the lists of the "lotes" which passed the K constant
{
	Apontador p;

	for (p = List->Primeiro->Prox; p != NULL; p = p->Prox)
	{
		if (p->Inactive >= k)
		{
			if (p == List->Ultimo)
			{
				List->Ultimo = p->Ante;
				List->Ultimo->Prox = NULL;
			}
			else
			{
				p->Ante->Prox = p->Prox;
  				p->Prox->Ante = p->Ante;
			}
			v[p->Pair] = 1;
			freeLLists(p);
			free(p);
		}
	}
}

void freeBLists (TBList *List) // Frees the big lists
{
	Apontador p;
	
	for (p=List->Primeiro; p != NULL; p = p->Prox)
	{
		freeLLists(p);
		free(p);
	}
}


int checkMsgToPrint (TBCell *p, int actualOrd) // Does a checking to know if the actual order is the same of the last printed order
{
	if(checkTBList(p) == 1)
		return 0;
	Pointer q;
	q = p->First->Next;
	
	if(q->message.ord == p->nextOrd && q->message.ord == actualOrd)
	{
		printf("%d;%d;%s\n", p->Pair, q->message.ord, q->message.msg);
		
		if(q == p->Last)
		{
			p->Last = q->Prev;
			p->Last->Next = NULL;
		}
		else
		{
			q->Prev->Next = q->Next;
			q->Next->Prev = q->Prev;
		}
		free(q);
		p->nextOrd++;
		p->Counter++;
		return 1;
	}	
	else if(q->message.ord == p->nextOrd && q->message.ord != actualOrd)
		return 1;
	else
		return 0;
	
}

void sendMessages(TBList *List) // Function to send the messages and to check if the message can be sent and printed in the stdout
{
	int actualOrd, aux;
	actualOrd = 1;
	aux = 0;
	Apontador p;
	p = List->Primeiro->Prox;
	
	while (1)
	{
		if (p == NULL && aux != 0)
		{
			p = List->Primeiro->Prox;
			aux = 0;
			actualOrd++;
		}
		else if (p == NULL && aux == 0)
			return;
		
		aux += checkMsgToPrint(p, actualOrd);
		p = p->Prox;
	}
}

	void readInput(TBList *List) // Reads the input from the stdin and stores in adequate variables
{
	TItem item;
	char lote[20], *nomelote;
	int par, k, nlote;
	
	scanf("%d", &k);
	getchar();

	while (1)
	{
		fgets(lote, 20, stdin);
		if (strcmp(lote, "-1\n") == 0) // Checks if the the both strings are equal
			break;
		nomelote = strtok(lote, " ");
		nlote = atoi(strtok(NULL, "\n"));
		incrementK(List);
		while (1)
		{
			scanf("%d;%d;", &par, &item.ord);
			fgets(item.msg, 501, stdin);
			strtok(item.msg, "\n");
			if(strcmp(item.msg, "Fim") == 0) // Checks if the the both strings are equal
				break;
			insertionInPlace(List, par, item);
		}
		int *v;
		v = calloc(MAX,sizeof(int));

		printf("Lote_%d:\n", nlote);
		printf("Listas:\n");
		printAllLists(List);
		printf("Envios:\n");
		sendMessages(List);
		printf("Contadores:\n");
		printCounters(List);
		freeK(List, k, v);
	}
}

void createBList (TBList **List) // Creates an empty big list
{
	
	(*List) = malloc(sizeof(TBList));
	(*List)->Primeiro = malloc(sizeof(TBCell));
	(*List)->Ultimo = (*List)->Primeiro;
	(*List)->Primeiro->Prox = NULL;
}

int emptyCheck (TBList *List) // Returns true (1) if the list is empty, and false (0) if the list isn't empty
{
	return (List->Primeiro == List->Ultimo);
}

Apontador searchPair (TBList *List, int pair) // Verificates if the pair already exists on the list and return the poir (if they are the same) or return NULL (if the pair doesn't exist)
{
	Apontador aux;
	
	for(aux = List->Primeiro->Prox; aux != NULL; aux = aux->Prox)
	{
		if(aux->Pair == pair)
			return aux;
	}
	return (NULL);
}

void insertionInPlace (TBList *List, int pair, TItem item) // Does the insertion in the right place, so it ordenates the list
{
	Apontador Celula, aux;

	if (emptyCheck(List) == 1) // Checks if the list is empty and inserts the cell on the last position of the list
	{
		Celula = malloc(sizeof(TBCell));
		Celula->Pair = pair;
		Celula->First = malloc(sizeof(TLCell));
		Celula->Last = Celula->First;
		Celula->First->Next = Celula->Last;
		Celula->Last->Prev = Celula->First;
		Celula->Last->Next = malloc(sizeof(TLCell));
		Celula->Last->Next->Prev = Celula->Last;
		Celula->Last = Celula->Last->Next;
		Celula->Last->message = item;
		Celula->Ante = List->Primeiro;
		Celula->Prox = NULL;
		List->Ultimo = Celula;
		List->Primeiro->Prox = Celula;
		Celula->Counter = 0;
		Celula->Inactive = 0;
		Celula->nextOrd = 1;
	}
	else
	{
		aux = searchPair(List, pair);
		if (aux == NULL)
		{
			Celula = malloc(sizeof(TBCell));
			Celula->Pair = pair;
			Celula->First = malloc(sizeof(TLCell));
			Celula->Last = Celula->First;
			Celula->First->Next = Celula->Last;
			Celula->Last->Prev = Celula->First;
			Celula->Last->Next = malloc(sizeof(TLCell));
			Celula->Last->Next->Prev = Celula->Last;
			Celula->Last = Celula->Last->Next;
			Celula->Last->message = item;
			Celula->Counter = 0;
			Celula->Inactive = 0;
			Celula->nextOrd = 1;
						
			for (aux = List->Primeiro->Prox; aux != NULL; aux = aux->Prox)
			{
				if (Celula->Pair < aux->Pair)
				{
					Celula->Prox = aux;
					Celula->Ante = aux->Ante;
					aux->Ante = Celula;
					Celula->Ante->Prox = Celula;
					break;
				}
			}
			if (aux == NULL)
			{
				Celula->Prox = NULL;
				Celula->Ante = List->Ultimo;
				List->Ultimo->Prox = Celula;
				List->Ultimo = Celula;
			}
		}
		else
		{
			Pointer p, q;
			q = malloc(sizeof(TLCell));
			q->message = item;
			for (p = aux->First->Next; p != NULL; p = p->Next)
			{
				if (q->message.ord < p->message.ord)
				{
					q->Next = p;
					q->Prev = p->Prev;
					p->Prev->Next = q;
					p->Prev = q;
					break;
				}
			}
			if (p == NULL)
			{
				q->Next = NULL;
				q->Prev = aux->Last;
				aux->Last->Next = q;
				aux->Last = q;
			}
			aux->Inactive = 0;
		}
	}
}

void printTLList (TBCell *List) // Prints the list in the required output way
{	
	Pointer p;

	printf("Par_%d:[", List->Pair);
	if (checkTBList(List))
	{
		printf("]\n");
		return;
	}
	for (p = List->First->Next; p != NULL; p = p->Next)
	{
		printf("(%d,", p->message.ord);
		printf("%s)", p->message.msg);
		if (p == List->Last)
		{
			printf("]");
			break;
			
		}
		else if (p != List->Last)
		{
			printf(",");
		}
	}
	printf("\n");
}

void printCounters (TBList *List) // Print the counters of each pair of list
{
	Apontador p;

	for (p = List->Primeiro->Prox; p != NULL; p = p->Prox)
	{
		printf("Par_%d:%d\n", p->Pair, p->Counter);
	}
}

void printAllLists (TBList *List) // Function to call the printTLList function
{
	Apontador p;

	for (p = List->Primeiro->Prox; p != NULL; p = p->Prox)
	{
		printTLList(p);
	}
}
