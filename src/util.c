#include "../lib/util.h"

void RBT_printReverseIndexTreeNodeValue(RBT *h) {
    printf("'%s' ", h->key);
}

void RBT_printReverseIndexTreeNode(RBT *h) {
    printf("Node: '%s' -> [", h->key);
    RBT_runOnAll_inOrder(h->value, RBT_printReverseIndexTreeNodeValue);
    puts("]");
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