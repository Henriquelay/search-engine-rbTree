#ifndef SEARCH_H_
#define SEARCH_H_

#include "rbTree.h"
#include "page.h"

#include <unistd.h>
#include <string.h>

void search(char* line, RBT* symbol_table);

void print_output(RBT* symbol_table);

#endif