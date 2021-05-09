#ifndef SEARCH_H_
#define SEARCH_H_

#include "rbTree.h"
#include "page.h"

#include <unistd.h>
#include <string.h>

RBT* search(char* line, RBT* symbol_table);

void print_output(RBT* symbol_table, RBT* page_graph);

#endif