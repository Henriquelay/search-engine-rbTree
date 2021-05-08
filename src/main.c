#include "../lib/reader.h"
#include "../lib/search.h"
#include <stdio.h>



void RBT_printReverseIndexTreeNodeValue(RBT *h){
    printf("'%s'\n", h->key);
}


void RBT_freeReverseIndexNode(RBT *h) {
    if (h == NULL) {
        return;
    }
    free(h->key);
    RBT_destroy(h->value);
    free(h);
}

void RBT_freeReverseIndexTree(RBT *tree) {
    RBT_runOnAll_postOrder(tree, RBT_freeReverseIndexNode);
}

// void RBT_printReverseIndexTreeNode(RBT *h) {
//     printf("Node: '%s' -> [", h->key);
//     RBT_runOnAll_inOrder(h, Page_print);
//     puts("]");
// }

void RBT_freePagesTreeNode(RBT *h) {
    Page_destroy(h->value);
    free(h->key);
    free(h);
}

void RBT_freePagesTree(RBT *h) {
    RBT_runOnAll_postOrder(h, RBT_freePagesTreeNode);
}

void RBT_printPagesTreeNode(RBT *h) {
    printf("Node: '%s' -> ", h->key);
    Page_print(h->value);
}

// Sim a main está muito bloated. Talvez explortar pra um util.c?
// Não juntar nas libs das bibliotecas, pq é específico pra essa solução
int main(int argc, char **argv){
    char *fileSource = argv[1];
    RBT *wordsTree = NULL;

    RBT *pagesTree = readData(fileSource, &wordsTree);
    puts("Words Tree:");
    RBT_runOnAll_inOrder(wordsTree, RBT_printReverseIndexTreeNodeValue);
    // puts("Pages Tree:");
    // RBT_runOnAll_inOrder(pagesTree, RBT_printPagesTreeNode);

    readGraph(fileSource, pagesTree);
    puts("Pages TreeGraph after grafada braba:");
    RBT_runOnAll_inOrder(pagesTree, RBT_printPagesTreeNode);
    
    printf("ESTOU TESTANDO AAAAAAAA\n");
    puts("Words Tree:");
    RBT_runOnAll_inOrder(wordsTree, RBT_printReverseIndexTreeNodeValue);
    printf("############## NÃO LIGO PRA CIMA  ######################\n");
    char teste[20] = "maca abacate";
    search(teste, wordsTree);

    RBT_freeReverseIndexTree(wordsTree);
    RBT_freePagesTree(pagesTree);
}
