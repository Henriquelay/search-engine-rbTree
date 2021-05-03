#include "../lib/data.h"

char *strlwr(char *string) {
    for (int i = 0; i < strlen(string); i++) {
        string[i] = tolower(string[i]);
    }
    return string;
}

int countLine(FILE *file) {
    int count = 0;
    while (!feof(file)) {
        char *s = malloc(1000 * sizeof(char));
        size_t tamanho = 1000;
        ssize_t nRead = getline(&s, &tamanho, file);
        // check_getLine(nRead);
        nRead = nRead;
        if (nRead != EOF) {
            count++;
        }
        free(s);
    }
    rewind(file);
    return count;
}

RBT *readData(char *fileSource, RBT *tree) {
    RBT *stopTree = NULL;
    char *stopFileAux = malloc(1000 * sizeof(char));
    stpcpy(stopFileAux, fileSource);
    strcat(stopFileAux, "/stopwords.txt");
    char *stopFile = strdup(stopFileAux);
    free(stopFileAux);
    FILE *stops = fopen(stopFile, "r");
    free(stopFile);
    // int numStopWord = countLine(stops);
    stopTree = readStops(stopTree, stops);
    fclose(stops);
    char *indexFileAux = malloc(1000 * sizeof(char));
    stpcpy(indexFileAux, fileSource);
    strcat(indexFileAux, "/index.txt");
    char *indexFile = strdup(indexFileAux);
    free(indexFileAux);
    FILE *index = fopen(indexFile, "r");
    int numPages = countLine(index);
    char *line = malloc(1000 * sizeof(char));
    for (int i = 0; i < numPages; i++) {
        int nItensRead = fscanf(index, "%s", line);
        // check_fscanf(nItensRead);
        if (nItensRead != EOF) {
            tree = readPage(tree, line, fileSource, stopTree);
        }
        memset(line, '\0', 1000);
    }
    RBT_free(stopTree);
    free(indexFile);
    free(line);
    fclose(index);
    return tree;
}

RBT *readPage(RBT *tree, char *pageName, char *filesouce, RBT *stopwords) {
    char *filenameAux = malloc(1000 * sizeof(char));
    strcpy(filenameAux, filesouce);
    strcat(filenameAux, "/pages/");
    strcat(filenameAux, pageName);
    char *fileName = strdup(filenameAux);
    free(filenameAux);
    FILE *file = fopen(fileName, "r");
    free(fileName);
    char *word = malloc(1000 * sizeof(char));
    while (!feof(file)) {
        int nItensRead = fscanf(file, "%s", word);
        // check_fscanf(nItensRead);
        char *finalWord = strdup(word);
        if (nItensRead != EOF) {
            finalWord = strlwr(finalWord);
            if (!search(stopwords, finalWord)) {
                tree = RBT_insert(tree, finalWord, pageName);
            }
        }
        free(finalWord);
        memset(word, '\0', 1000);
    }
    fclose(file);
    free(word);
    return tree;
}

RBT *readStops(RBT *tree, FILE *file) {
    char *word = malloc(1000 * sizeof(char));
    while (!feof(file)) {
        int nItensRead = fscanf(file, "%s", word);
        // check_fscanf(nItensRead);
        char *finalWord = strdup(word);
        //colocar as finalwords em vermelha e preta ficou gambiarrado
        if (nItensRead != EOF) {
            tree = RBT_insert(tree, finalWord, finalWord);
        }

        free(finalWord);
        memset(word, '\0', 1000);
    }
    free(word);
    return tree;
}

List *readGraph(char *filesource) {
    char *graph_file_name = malloc(1000 * sizeof(char));
    strcpy(graph_file_name, filesource);
    strcat(graph_file_name, "/graph.txt");
    GraphNode *pagesTree = NULL;
    List *pagesList = malloc(sizeof(List));
    newList(pagesList);

    char *line = NULL;
    size_t len = 0;
    printf("O arquivo é %s\n", graph_file_name);
    FILE *graph_file = fopen(graph_file_name, "r");
    while (!feof(graph_file)) {
        ssize_t nRead = getline(&line, &len, graph_file);
        // check_getLine(nRead);
        if (nRead != EOF) {
            char pageName[1000];
            int numberOfLinks;
            int numberOfReadChars;
            sscanf(line, "%s %d %n", pageName, &numberOfLinks, &numberOfReadChars);
            line = line + numberOfReadChars;

            Page **linkedPages = getPageReferences(line, numberOfLinks, pagesTree);
            Page *thisPage = initializePage(pageName, -1, numberOfLinks, linkedPages);
            pagesTree = GraphNode_insert(
                pagesTree, thisPage->pageName, thisPage, 1, copyPage);
            Page *thisPageInNodeRef = pagesTree->data;
            if (thisPage != thisPageInNodeRef) {
                freePage(thisPage, 0);
            }
            addTail(pagesList, thisPageInNodeRef);
        }
    }

    return pagesList;
}

Page **getPageReferences(char *line, int numberOfLinks, GraphNode *pagesTree) {
    Page **linkedPages = malloc(numberOfLinks * sizeof(Page *));
    int nCharacterRead;
    for (int i = 0; i < numberOfLinks; i++) {
        char linkedPage[1000];
        sscanf(line, "%s %n", linkedPage, &nCharacterRead);
        line = line + nCharacterRead;

        GraphNode *pageNode = searchGT(pagesTree, linkedPage);
        if (!pageNode) {
            Page *newPage = malloc(sizeof(Page));
            newPage->listPages = NULL;
            newPage->nOutLinks = -1;
            newPage->pageName = strdup(linkedPage);
            newPage->powerRank = -1;
            linkedPages[i] = newPage;
            GraphNode_insert(pagesTree, linkedPage, newPage, 0, NULL);
        } else {
            linkedPages[i] = (Page *)pageNode->data;
        }
    }
    return linkedPages;
}
