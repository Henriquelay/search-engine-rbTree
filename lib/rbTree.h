#ifndef RBTREE_H_
#define RBTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node RBT;

struct node {
    char *key;
    void *value;
    char color;
    RBT *l, *r;
};

RBT *RBT_search(RBT *n, char *key);
RBT *RBT_insert(RBT *h, char *key, void *val);
void RBT_free(RBT *h);

void RBT_runOnAll_inOrder(RBT *h, void (*visit)(RBT *));
void RBT_print(RBT *h);

//nossas

#endif // !RBTREE_H_
