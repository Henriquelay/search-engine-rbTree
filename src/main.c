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

int main(int argc, char **argv) {
    char *fileSource = argv[1];
    RBT *tree = NULL;

    readData(fileSource, &tree);
    puts("Words Tree:");
    RBT_runOnAll_inOrder(tree, RBT_printReverseIndexTreeNode);

    // readGraph(fileSource, tree);

    RBT_freeReverseIndexTree(tree);

    // Node *pageNode = pageList->head;
    // printf("Vou printar as paginas\n");
    // while (pageNode != NULL) {
    //     printPage(pageNode->page);
    //     pageNode = pageNode->next;
    // }
}
