#include "../lib/reader.h"
#include <stdio.h>

void RBT_freeReverseIndexNode(RBT *h) {
    if (h == NULL) {
        return;
    }
    free(h->key);
    list_destroy(h->value, 1);
    free(h);
    h = NULL;
}

void RBT_freeReverseIndexTree(RBT *tree) {
    RBT_runOnAll_postOrder(tree, RBT_freeReverseIndexNode);
}

void RBT_printReverseIndexTreeNode(RBT *h) {
    printf("Node: '%s' -> [", h->key);
    list_print(h->value, "'%s' ");
    puts("]");
}

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
int main(int argc, char **argv) {
    char *fileSource = argv[1];
    RBT *wordsTree = NULL;

    RBT *pagesTree = readData(fileSource, &wordsTree);
    puts("Words Tree:");
    RBT_runOnAll_inOrder(wordsTree, RBT_printReverseIndexTreeNode);
    // puts("Pages Tree:");
    // RBT_runOnAll_inOrder(pagesTree, RBT_printPagesTreeNode);

    readGraph(fileSource, pagesTree);

    puts("Pages TreeGraph after grafada braba:");
    RBT_runOnAll_inOrder(pagesTree, RBT_printPagesTreeNode);

    RBT_freeReverseIndexTree(wordsTree);
    RBT_freePagesTree(pagesTree);
}
