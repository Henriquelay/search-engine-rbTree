#include "../lib/reader.h"
#include <stdio.h>

void RBT_freeReverseIndexNode(RBT *h) {
    if (h == NULL) {
        return;
    }
    free(h->key);
    list_destroy(h->value);
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

void RBT_printPagesTreeNode(RBT *h) {
    printf("Node: '%s' -> ", h->key);
    Page_print(h->value);
}

int main(int argc, char **argv) {
    char *fileSource = argv[1];
    RBT *wordsTree = NULL;

    RBT *pagesTree = readData(fileSource, &wordsTree);
    puts("Words Tree:");
    RBT_runOnAll_inOrder(wordsTree, RBT_printReverseIndexTreeNode);
    // puts("Pages Tree:");
    // RBT_runOnAll_inOrder(pagesTree, RBT_printPagesTreeNode);

    readGraph(fileSource, pagesTree);

    puts("Pages Tree after grafada braba:");
    RBT_runOnAll_inOrder(pagesTree, RBT_printPagesTreeNode);

    RBT_freeReverseIndexTree(wordsTree);

    // Node *pageNode = pageList->head;
    // printf("Vou printar as paginas\n");
    // while (pageNode != NULL) {
    //     printPage(pageNode->page);
    //     pageNode = pageNode->next;
    // }
}
