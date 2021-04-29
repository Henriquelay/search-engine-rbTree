#include"../lib/data.h"


void readData(char* fileSource, RBT* tree){
  RBT* stopTree;
  FILE* stops = fopen(strcat(fileSource,"/stopwords.txt"),"r");
  // int numStopWord = countLine(stops);
  stopTree = readStops(stopTree,stops);
  fclose(stops);

  FILE* index = fopen(strcat(fileSource,"/index.txt"),"r");
  int numPages= countLine(index);
  char* line = malloc(1000*sizeof(char));
  for(int i = 0;i<numPages;i++){
    fscanf(index,"%s",line);
    tree = readPage(tree,line,fileSource,stopTree);
    memset(line,'\0',1000);
  }
  free(line);
  fclose(index);
}



int countLine(FILE* file){
  int count = 0;
  while(!feof(file)){
    char* s = malloc(1000*sizeof(char));
    size_t tamanho=1000;
    getline(&s,&tamanho,file);
    count++;
  }
  rewind(file);
  return count;
}
RBT* readPage(RBT* tree, char* pageName, char* filesouce, RBT* stopwords){
  FILE* file = fopen(strcat(strcat(filesouce,"/pages/"),pageName),"r");
  char* word = malloc(1000*sizeof(char));
  while(!feof(file)){
    fscanf(file,"%s",word);
    char* finalWord = strdup(word);
    if(!search(stopwords,finalWord)){
      tree = RBT_insert(tree,finalWord,pageName);
    }
    memset(word,'\0',1000);
  }
  fclose(file);
  free(word);
  return tree;
}
RBT* readStops(RBT* tree,FILE* file){
  char* word = malloc(1000*sizeof(char));
  while(!feof(file)){
    fscanf(file,"%s",word);
    char* finalWord = strdup(word);
    //colocar as finalwords em vermelha e preta ficou gambiarrado
    tree = RBT_insert(tree,finalWord,finalWord);
    memset(word,'\0',1000);
  }
  free(word);
  return tree;
}