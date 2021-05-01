#include"../lib/data.h"


char* strlwr(char* string){
  for(int i=0; i< strlen(string);i++){
    string[i] = tolower(string[i]);
  }
  return string;
}


int countLine(FILE* file){
  int count = 0;
  while(!feof(file)){
    char* s = malloc(1000*sizeof(char));
    size_t tamanho=1000;
    ssize_t nRead = getline(&s,&tamanho,file);
    check_getLine(nRead);
    count++;
    free(s);
  }
  rewind(file);
  return count;
}


RBT* readData(char* fileSource, RBT* tree){
  RBT* stopTree=NULL;
  char* stopFileAux = malloc(1000*sizeof(char));
  stpcpy(stopFileAux,fileSource);strcat(stopFileAux,"/stopwords.txt");
  char* stopFile = strdup(stopFileAux);
  free(stopFileAux);
  FILE* stops = fopen(stopFile,"r");
  free(stopFile);
  // int numStopWord = countLine(stops);
  stopTree = readStops(stopTree,stops);
  fclose(stops);
  char* indexFileAux = malloc(1000*sizeof(char));
  stpcpy(indexFileAux,fileSource);strcat(indexFileAux,"/index.txt");
  char* indexFile = strdup(indexFileAux);
  free(indexFileAux);
  FILE* index = fopen(indexFile,"r");
  int numPages= countLine(index);
  char* line = malloc(1000*sizeof(char));
  for(int i = 0;i<numPages;i++){
    int nItensRead = fscanf(index,"%s",line);
    check_fscanf(nItensRead);
    tree = readPage(tree,line,fileSource,stopTree);
    memset(line,'\0',1000);
  }
  RBT_free(stopTree);
  free(indexFile);
  free(line);
  fclose(index);
  return tree;
}


RBT* readPage(RBT* tree, char* pageName, char* filesouce, RBT* stopwords){
  char* filenameAux = malloc(1000*sizeof(char));
  strcpy(filenameAux,filesouce);
  strcat(filenameAux,"/pages/");
  strcat(filenameAux,pageName);
  char* fileName = strdup(filenameAux);
  free(filenameAux);
  FILE* file = fopen(fileName,"r");
  free(fileName);
  char* word = malloc(1000*sizeof(char));
  while(!feof(file)){
    int nItensRead = fscanf(file,"%s",word);
    check_fscanf(nItensRead);
    char* finalWord = strdup(word);
    finalWord = strlwr(finalWord);
    if(!search(stopwords,finalWord)){
      
      tree = RBT_insert(tree,finalWord,pageName);
    }
    free(finalWord);
    memset(word,'\0',1000);
  }
  fclose(file);
  free(word);
  return tree;
}


RBT* readStops(RBT* tree,FILE* file){
  char* word = malloc(1000*sizeof(char));
  while(!feof(file)){
    int nItensRead = fscanf(file,"%s",word);
    check_fscanf(nItensRead);
    char* finalWord = strdup(word);
    finalWord = strlwr(finalWord); 
    //colocar as finalwords em vermelha e preta ficou gambiarrado
    tree = RBT_insert(tree,finalWord,finalWord);
    free(finalWord);
    memset(word,'\0',1000);
  }
  free(word);
  return tree;
}

