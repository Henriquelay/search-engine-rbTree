#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/linkedList.h"

void newList(List* list)
{

	list->head = NULL;
	list->tail = NULL;
}


int destroyList(List * list)
{

	while(list->head)
    {
		Node* current = list->head;
		list->head = current->next;
		free(current);
	}

	return 0;
}


int addTail(List* list, Page* pagePointer)
{

	Node* node = (Node*)malloc(sizeof(Node));
	checkNullPointer(node, "Problema na alocação de novo nó da lista.\n");
	node->page = pagePointer;
	node->next = NULL;

	if(!list->head)
		list->head = node;


	if(list->tail)
		list->tail->next = node;

	list->tail = node;

	return 0;

}