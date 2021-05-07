#ifndef DATA_H_
#define DATA_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rbTree.h"
#include "list.h"
#include "page.h"

void readData(char* folderName, RBT** tree);
RBT* readGraph(char* filesource, RBT* tree);

#endif // !DATA_H_#
