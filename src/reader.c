#include "../lib/reader.h"

#define BUFFERSIZE (250)

char *strlwr(char *string) {
    for (int i = 0; i < strlen(string); i++) {
        string[i] = tolower(string[i]);
    }
    return string;
}

void *RBT_collision_appendOnList(RBT *node, void *val) {
    // Newly-created node
    if (node->value == NULL) {
        list_t *list = list_init();
        list_push(list, val);
        return list;
    }
    list_push(node->value, val);
    return node->value;
}

void readPage(RBT **tree, char *pageName, char *pagesFolder, RBT *stopwords) {
    // Reading the page file:
    // Buiding pageFile path
    char filePath[strlen(pageName) + strlen(pagesFolder) + 1];
    strcpy(filePath, pagesFolder);
    strcat(filePath, pageName);

    char *wordBuffer = NULL;
    size_t wordBufferSize = 0;
    // '\n' delimiter is already treated by using getline
    char delimiters[] = {' ', '\t', '\0'};

    FILE *pageFile = fopen(filePath, "r");
    if (pageFile == NULL) {
        fprintf(stderr, "Error opening file '%s'", filePath);
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    // For each line
    while (getline(&wordBuffer, &wordBufferSize, pageFile) != -1) {
        // Overwriting '\0' on last '\n'
        size_t len = strlen(wordBuffer);
        if (wordBuffer[len - 1] == '\n') {
            wordBuffer[len - 1] = '\0';
        }
        // For each keyword
        char *trimmedKeyword;
        for (trimmedKeyword = strtok(wordBuffer, delimiters); trimmedKeyword != NULL; trimmedKeyword = strtok(NULL, delimiters)) {
            char *treatedKeyword = strlwr(trimmedKeyword);
            // If isn't a stopword
            if (RBT_search(stopwords, treatedKeyword) == NULL) {
                // Start new list and push pageName on it
                char *dupStr = strdup(pageName);
                if (dupStr == NULL) {
                    perror("Not enough memory to insert page name on wordTree");
                    exit(EXIT_FAILURE);
                }
                // Insert on tree
                *tree = RBT_insert(*tree, treatedKeyword, dupStr, RBT_collision_appendOnList);
            }
        }
    }
    fclose(pageFile);
    free(wordBuffer);
}

void RBT_printStopTreeNode(RBT *h) {
    printf("Node: '%s' -> %p\n", h->key, h->value);
}

void *RBT_callback_stopWords(RBT *node, void *value) {
    return NULL;
}

RBT *readStopsFile(RBT *tree, FILE *file) {
    char word[BUFFERSIZE];
    while (!feof(file)) {
        if (fscanf(file, "%s", word) == EOF) {
            perror("Error reading stopwords");
            exit(EXIT_FAILURE);
        }
        // Using RBTree as set
        // Can user collisionFn as NULL since there won't be repeated stopWords on a well-behaved input
        tree = RBT_insert(tree, strlwr(word), NULL, RBT_callback_stopWords);
    }
    return tree;
}

RBT *buildStopwordsTree(char *fileSource) {
    // Building stopFile path
    char appendsStopword[] = "/stopwords.txt";
    char stopWordsFilePath[strlen(fileSource) + strlen(appendsStopword) + 1];
    strcpy(stopWordsFilePath, fileSource);
    strcat(stopWordsFilePath, appendsStopword);
    FILE *stopsWordsFile = fopen(stopWordsFilePath, "r");
    if (stopsWordsFile == NULL) {
        fprintf(stderr, "Error opening file '%s'", stopWordsFilePath);
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    // Reading stopwords from file
    RBT *stopTree = NULL;
    stopTree = readStopsFile(stopTree, stopsWordsFile);
    fclose(stopsWordsFile);
    return stopTree;
}

void readPages(char *fileSource, RBT **tree, RBT *stopTree) {
    // Reading index
    // Building indexFile path
    char appendsIndex[] = "/index.txt";
    char indexFilePath[strlen(fileSource) + strlen(appendsIndex) + 1];
    strcpy(indexFilePath, fileSource);
    strcat(indexFilePath, appendsIndex);

    // Reading pages
    // Building pagesFolder path
    char appendsPages[] = "/pages/";
    char pageFolderPath[strlen(fileSource) + strlen(appendsPages) + 1];
    strcpy(pageFolderPath, fileSource);
    strcat(pageFolderPath, appendsPages);

    // Mapping words to files

    char *pageName = NULL;
    size_t pageNameBufferSize = 0;

    FILE *indexFile = fopen(indexFilePath, "r");
    if (indexFile == NULL) {
        fprintf(stderr, "Error opening file '%s'", indexFilePath);
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    // '\n' delimiter is already treated by using getline
    // For each line
    while (getline(&pageName, &pageNameBufferSize, indexFile) != -1) {
        // Trimming trailing '\n'
        if (pageName[strlen(pageName) - 1] == '\n') {
            pageName[strlen(pageName) - 1] = '\0';
        }
        readPage(tree, pageName, pageFolderPath, stopTree);
    }
    fclose(indexFile);
    free(pageName);
}

void readData(char *fileSource, RBT **tree) {
    RBT *stopTree = buildStopwordsTree(fileSource);
    // puts("Stopwords Tree:");
    // RBT_runOnAll_inOrder(stopTree, RBT_printStopTreeNode);

    readPages(fileSource, tree, stopTree);
    RBT_destroy(stopTree);
}

/**
 * Reads graph.txt on folder, builds the 
 * */
RBT *readGraph(char *filesource, RBT *tree) {
    // Building file path
    char appends[] = "/graph.txt";
    char graphFilePath[strlen(filesource) + strlen(appends) + 1];
    strcpy(graphFilePath, filesource);
    strcat(graphFilePath, "/graph.txt");
    printf("Reading from graph file '%s'\n", graphFilePath);

    FILE *graphFile = fopen(graphFilePath, "r");
    if (graphFile == NULL) {
        fprintf(stderr, "Error opening file '%s'", graphFilePath);
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    char *lineBuffer = NULL;
    size_t lineBufferSize = 0;
    while (getline(&lineBuffer, &lineBufferSize, graphFile) != -1) {
        char pageName[BUFFERSIZE];
        int numberOfLinks;
        int numberOfReadChars;
        sscanf(lineBuffer, "%s %d%n", pageName, &numberOfLinks, &numberOfReadChars);

        // Dislocating line to beggining of links array
        lineBuffer += numberOfReadChars;

        char currentFileLink[BUFFERSIZE];
        for (unsigned int i = 0; i < numberOfLinks; i++) {
            sscanf(lineBuffer, " %s", currentFileLink);
            printf("Arquivo lido: %s\n", currentFileLink);
        }
        // Page *thisPage = initializePage(pageName, -1, numberOfLinks, linkedPages);
        // pagesTree = GraphNode_insert(
        //     pagesTree, thisPage->pageName, thisPage, 1, copyPage);
        // Page *thisPageInNodeRef = pagesTree->data;
        // if (thisPage != thisPageInNodeRef) {
        //     freePage(thisPage, 0);
        // }
        // addTail(pagesList, thisPageInNodeRef);
    }

    return NULL;
}
