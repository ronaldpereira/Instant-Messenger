#ifndef lists
#define lists

typedef struct TypeItem
{
	int ord; // Order of the input message
	char msg[501]; // Message in the input
} TItem;

typedef struct LittleCell *Pointer; // Pointer to the little cell

typedef struct LittleCell
{
	TItem message; // Type item message
	Pointer Next, Prev; // Next and previous of the little cell
} TLCell;

typedef int TPair; // Typedef of pair
typedef int TAuxiliar; // Typedef of auxiliar variables

typedef struct BigCell *Apontador; // Pointer to the big cell

typedef struct BigCell
{
	Pointer First, Last; // Pointer to the first cell of the little cell
	Apontador Prox, Ante; // Pointer to the next and previous of the big cell
	TPair Pair; // Stores the actual pair
	TAuxiliar Counter; // Stores the counter of sent messages
	TAuxiliar Inactive; // Stores the "K" of each inactive 'lote' of each pair
	TAuxiliar nextOrd; // Stores the next order to be sent
} TBCell;

typedef struct BigList
{
	Apontador Primeiro, Ultimo; // Pointer to the first and the last of the big cell
} TBList;


int checkTBList (TBCell *List);
void freeLLists (TBCell *List);
void freeK (TBList *List, int k, int *v);
void freeBLists (TBList *List);
int checkMsgToPrint (TBCell *p, int actualOrd);
void sendMessages(TBList *List);
void readInput(TBList *List);
void createBList (TBList **List);
int emptyCheck (TBList *List);
Apontador searchPair (TBList *List, int pair);
void insertionInPlace (TBList *List, int pair, TItem item);
void printTLList (TBCell *List);
void printCounters (TBList *List);
void printAllLists (TBList *List);

#endif
