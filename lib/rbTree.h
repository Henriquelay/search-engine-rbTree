#ifndef RBTREE_H_
#define RBTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "page.h"

#define RED (1)
#define BLK (0)

typedef struct node RBT;

struct node {
    char *key;
    void *value;
    char color;
    RBT *l, *r;
};

RBT *RBT_search(RBT *n, char *key);
RBT *RBT_insert(RBT *h, char *key, void* value, void *(*callBack)(RBT *node, void* value));
// void RBT_free(RBT *h); // Commented out for user to supply own free function with the runOnAll helpers

void RBT_runOnAll_preOrder(RBT *h, void (*visit)(RBT *));
void RBT_runOnAll_inOrder(RBT *h, void (*visit)(RBT *));
void RBT_runOnAll_postOrder(RBT *h, void (*visit)(RBT *));

void RBT_destroy(RBT *h);

Page** RBT_value_to_array(RBT *h, int* array_size, RBT* page_graph);
//nossas

#endif // !RBTREE_H_
