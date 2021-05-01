#include<stdlib.h>
#include<stdio.h>
#include"../lib/data.h"
#include"../lib/rbTree.h"

void printaValues(RBT* arvre){
  if(arvre->l!=NULL){
  printaValues(arvre->l);
  }
  if(arvre->r!=NULL){
    printaValues(arvre->r);
  }
  puts(arvre->key);
}

void printaArvre(RBT* arvre){
  if(arvre->l!=NULL){
    printaArvre(arvre->l);
  }
  if(arvre->r!=NULL){
    printaArvre(arvre->r);
  }
  puts(arvre->key);
  puts("values:");
  printaValues(arvre->val);
  puts("-----------------");


}


int main(int argc, char**argv){
  char* fileSource = argv[1];
  RBT* tree=NULL;
  tree = readData(fileSource, tree);
  printaArvre(tree);
  RBT_free(tree);
}

