#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include <stdio.h>

/*
    Biblioteca list.h
    Contem a implementacao de uma lista encadeada generica
    e funcoes de pilha e fila (enqueue/dequeue e push/pop)
*/

typedef struct linked_node_t {
    void* value;
    struct linked_node_t* next;
    struct linked_node_t* previous;
} linked_node_t;

typedef struct list_t {
    linked_node_t* head;
    linked_node_t* tail;
    unsigned int count;
} list_t;

list_t* list_init();

char list_isEmpty(list_t* list);

void list_push(list_t* list, void* item);
void* list_pop(list_t* list);

void list_enqueue(list_t* list, void* item);
void* list_dequeue(list_t* list);

/*
    Executa uma funcao em todos os elementos de uma lista
*/
void list_runOnAll(list_t* list, void (*visit)(linked_node_t*));

void list_print(list_t* stack, const char* format);

void list_destroy(list_t *list, char freeInnerValue);

#endif
