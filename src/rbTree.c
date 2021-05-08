#include "../lib/rbTree.h"

RBT *RBT_search(RBT *n, char *key) {
    while (n != NULL) {
        int cmp;
        cmp = strcmp(key, n->key);
        if (cmp < 0)
            n = n->l;
        else if (cmp > 0)
            n = n->r;
        else
            return n;
    }
    return NULL;
}

int is_red(RBT *x) {
    if (x == NULL)
        return 0;
    return x->color == RED; //RED == 1
}

RBT *RBT_rotate_left(RBT *h) {
    RBT *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED; //vermelho
    return x;
}

RBT *RBT_rotate_right(RBT *h) {
    RBT *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

void RBT_flip_colors(RBT *h) {
    h->color = RED;
    h->l->color = BLK;
    h->r->color = BLK;
}

RBT *create_node(char *key, char color, void* value, void *(*callBack)(RBT *node, void* value)) {
    RBT *new = malloc(sizeof(RBT));
    if (new == NULL) {
        perror("RBT node alloc failed");
        exit(EXIT_FAILURE);
    }
    new->key = strdup(key);
    new->color = color;
    new->l = new->r = NULL;
    new->value = NULL;
    new->value = callBack(new, value);
    return new;
}

/* CollisionFn should return h->value after updating it, in case of collision.
 * node->value will be set as NULL for newly-created nodes, and should return initial value.
 * */
RBT *RBT_insert(RBT *h, char *key, void* value, void *(*callBack)(RBT *node, void* value)) {
    // Insert at bottom and color it red.
    if (h == NULL) {
        return create_node(key, RED, value, callBack);
    }

    int cmp = strcmp(key, h->key);
    if (cmp < 0) {
        h->l = RBT_insert(h->l, key, value, callBack);
    } else if (cmp > 0) {
        h->r = RBT_insert(h->r, key, value, callBack);
    } else /*cmp == 0*/ {
        // Updating
        h->value = callBack(h, value);
    }
    // Lean left.
    if (is_red(h->r) && !is_red(h->l)) {
        h = RBT_rotate_left(h);
    }
    // Balance 4-node.
    if (is_red(h->l) && is_red(h->l->l)) {
        h = RBT_rotate_right(h);
    }
    // Split 4-node.
    if (is_red(h->l) && is_red(h->r)) {
        RBT_flip_colors(h);
    }
    return h;
}

void RBT_runOnAll_preOrder(RBT *h, void (*visit)(RBT *)) {
    if (h != NULL) {
        visit(h);
        RBT_runOnAll_preOrder(h->l, visit);
        RBT_runOnAll_preOrder(h->r, visit);
    }
}

void RBT_runOnAll_inOrder(RBT *h, void (*visit)(RBT *)) {
    if (h != NULL) {
        RBT_runOnAll_inOrder(h->l, visit);
        visit(h);
        RBT_runOnAll_inOrder(h->r, visit);
    }
}

void RBT_runOnAll_postOrder(RBT *h, void (*visit)(RBT *)) {
    if (h != NULL) {
        RBT_runOnAll_postOrder(h->l, visit);
        RBT_runOnAll_postOrder(h->r, visit);
        visit(h);
    }
}

void RBT_freeFunction(RBT *h) {
    free(h->key);
    //free(h->value);
    free(h);
}

// Only frees keys
void RBT_destroy(RBT *h) {
    
    RBT_runOnAll_postOrder(h, RBT_freeFunction);
}
