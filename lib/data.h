#ifndef DATA_H_
#define DATA_H_
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"./rbTree.h"

void readData(char* filename, RBT* tree);
int countLine(FILE* file);
RBT* readPage(RBT* tree, char* pageName, char* filesouce, RBT* stopwords);
RBT* readStops(RBT* tree,FILE* file);
#endif // !DATA_H_#