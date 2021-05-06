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

int main(int argc, char **argv) {
    char *fileSource = argv[1];
    RBT *tree = NULL;
    readData(fileSource, &tree);
    RBT_runOnAll_postOrder(tree, RBT_freeReverseIndexNode);
    // RBT_destroy(tree);
    // RBT_free(tree);

    // readGraph(fileSource);

    // Node *pageNode = pageList->head;
    // printf("Vou printar as paginas\n");
    // while (pageNode != NULL) {
    //     printPage(pageNode->page);
    //     pageNode = pageNode->next;
    // }
}
