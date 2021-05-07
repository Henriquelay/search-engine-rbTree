#include "../lib/reader.h"
#include <stdio.h>

void RBT_freeReverseIndexNode(RBT *h) {
    if (h == NULL)
        return;
    free(h->key);
    RBT_destroy(h->value);
    free(h);
    h = NULL;
}

void RBT_freeReverseIndexTree(RBT* tree) {
    RBT_runOnAll_postOrder(tree, RBT_freeReverseIndexNode);
}

int main(int argc, char **argv) {
    char *fileSource = argv[1];
    RBT *tree = NULL;
    readData(fileSource, &tree);
    // readGraph(fileSource, tree);

    RBT_freeReverseIndexTree(tree);

    // Node *pageNode = pageList->head;
    // printf("Vou printar as paginas\n");
    // while (pageNode != NULL) {
    //     printPage(pageNode->page);
    //     pageNode = pageNode->next;
    // }
}
