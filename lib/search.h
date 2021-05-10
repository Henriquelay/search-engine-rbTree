#ifndef SEARCH_H_
#define SEARCH_H_

#include "rbTree.h"
#include "page.h"
#include <unistd.h>
#include <string.h>

/*
    Biblioteca search.h
    Contem implementacao das funcoes de busca em paginas e
    saida do resultado.
*/

RBT* search(char* line, RBT* symbol_table);

void print_output(RBT* symbol_table, RBT* page_graph);

char *strlwr(char *string);

#endif