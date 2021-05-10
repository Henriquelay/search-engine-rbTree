#ifndef DATA_H_
#define DATA_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rbTree.h"
#include "list.h"
#include "page.h"

/*
    Biblioteca reader.h
    Contem implementacao das funcoes de leitura das entradas
    e criacao das arvores.
*/

RBT* readData(char* folderName, RBT** tree);
void readGraph(char* filesource, RBT* tree);
char *strlwr(char *string);

#endif // !DATA_H_#
