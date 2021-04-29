#include<stdlib.h>
#include<stdio.h>
#include"../lib/data.h"
#include"../lib/rbTree.h"
int main(int argc, char**argv){
  char* fileSource = argv[1];
  RBT* tree;
  readData(fileSource, tree);
}