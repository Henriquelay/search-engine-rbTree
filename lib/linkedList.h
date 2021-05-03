#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdlib.h>
#include "../lib/errorCheck.h"
#include "../lib/page.h"

typedef struct listNode
{
	Page* page;
	struct listNode* next;
}Node;


typedef struct
{
	Node* head; 		// Pointer to list head
	Node* tail;			// Pointer to list tail
}List;


void newList(List* list);


int destroyList(List* list);


int addTail(List* list, Page* pagePointer);


#endif