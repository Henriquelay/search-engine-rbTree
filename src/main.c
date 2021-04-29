#include<stdlib.h>
#include<stdio.h>
#include"../lib/data.h"
#include"../lib/rbTree.h"
int main(int argc, char**argv){
  char* fileSource = argv[1];
  puts(fileSource);
  RBT* tree=NULL;
  readData(fileSource, tree);
}