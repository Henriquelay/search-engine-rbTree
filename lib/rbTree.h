#ifndef RBTREE_H_
#define RBTREE_H_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct node RBT;

struct node {
  char* key;
  RBT* val;
  int color;
  RBT *l, *r;
};

int search(RBT *n, char* key);
RBT* rotate_left(RBT *h);
RBT* rotate_right(RBT *h);
void flip_colors(RBT *h);
RBT* RBT_insert(RBT *h, char* key, char* val);

//nossas

#endif // !RBTREE_H_
