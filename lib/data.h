#ifndef DATA_H_
#define DATA_H_
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"./rbTree.h"
#include "graphTree.h"
#include "errorCheck.h"
#include "linkedList.h"
#include "page.h"

RBT* readData(char* filename, RBT* tree);
int countLine(FILE* file);
RBT* readPage(RBT* tree, char* pageName, char* filesouce, RBT* stopwords);
RBT* readStops(RBT* tree,FILE* file);
List* readGraph(char* filesource);
Page** getPageReferences(char* line, int numberOfLinks, GraphNode* pagesTree);

#endif // !DATA_H_#