#include"../lib/rbTree.h"

// RBT* search(RBT *n, char* key) {
//   while (n != NULL) {
//   int cmp;
//   cmp = strcmp(key, n->key);
//   if (cmp < 0) n = n->l;
//   else if (cmp > 0) n = n->r;
//   else return n->val;
//   }
//   return NULL;
// }
int search(RBT *n, char* key) {
  while (n != NULL) {
  int cmp;
  cmp = strcmp(key, n->key);
  if (cmp < 0) n = n->l;
  else if (cmp > 0) n = n->r;
  else return 01;
  }
  return 0;
}

int is_red(RBT *x) {
  if (x == NULL) return 0;
  return x->color; //RED == 1
}

RBT* rotate_left(RBT *h) {
  RBT *x = h->r;
  h->r = x->l;
  x->l = h;
  x->color = x->l->color;
  x->l->color = 1;//vermelho
  return x;
}
RBT* rotate_right(RBT *h) {
  RBT *x = h->l;
  h->l = x->r;
  x->r = h;
  x->color = x->r->color;
  x->r->color = 1;
  return x;
}

void flip_colors(RBT *h) {
  h->color = 1;
  h->l->color = 0;
  h->r->color = 0;
}

RBT* create_values(char* val, int color){
  RBT* new = malloc(sizeof(RBT));
  new->key = strdup(val);
  new->val = NULL;
  new->color=color;
  new->l=new->r=NULL;
}
RBT* create_node(char* key, char* val, int color){
  RBT* new = malloc(sizeof(RBT));
  new->key = strdup(key);
  new->val = create_values(val,1);
  new->color=color;
  new->l=new->r=NULL;
}

RBT* RBT_insert(RBT *h, char* key, char* val) {
  // Insert at bottom and color it red.
  if (h == NULL) { return create_node(key, val, 1); }
  int cmp = strcmp(key, h->key);
  if (cmp < 0) { h->l = RBT_insert(h->l, key, val); }
  else if (cmp > 0) { h->r = RBT_insert(h->r, key, val); }
  else /*cmp == 0*/ { h->val = RBT_insert(h->val,val,key); }//antes era null talvez de problema
  // Lean left.
  if (is_red(h->r) && !is_red(h->l)) { h = rotate_left(h); }
  // Balance 4-node.
  if (is_red(h->l) && is_red(h->l->l)) { h = rotate_right(h); }
  // Split 4-node.
  if (is_red(h->l) && is_red(h->r)) { flip_colors(h); }
  return h;
}