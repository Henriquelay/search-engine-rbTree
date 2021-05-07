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
    return x->color; //RED == 1
}

RBT *RBT_rotate_left(RBT *h) {
    RBT *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = 1; //vermelho
    return x;
}

RBT *RBT_rotate_right(RBT *h) {
    RBT *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = 1;
    return x;
}

void RBT_flip_colors(RBT *h) {
    h->color = 1;
    h->l->color = 0;
    h->r->color = 0;
}

RBT *create_values(void *val, char color) {
    // Won't create values if NULL is passed on insert
    if (val == NULL) {
        return NULL;
    }
    RBT *new = malloc(sizeof(RBT));
    if (new == NULL) {
        perror("RBT value alloc failed");
        exit(EXIT_FAILURE);
    }
    new->key = strdup(val);
    new->value = NULL;
    new->color = color;
    new->l = new->r = NULL;
    return new;
}

RBT *create_node(char *key, void *val, char color) {
    RBT *new = malloc(sizeof(RBT));
    if (new == NULL) {
        perror("RBT node alloc failed");
        exit(EXIT_FAILURE);
    }
    new->key = strdup(key);
    new->value = create_values(val, 1);
    new->color = color;
    new->l = new->r = NULL;
    return new;
}

RBT *RBT_insert(RBT *h, char *key, void *val) {
    // Insert at bottom and color it red.
    if (h == NULL) {
        return create_node(key, val, 1);
    }

    int cmp = strcmp(key, h->key);
    if (cmp < 0) {
        h->l = RBT_insert(h->l, key, val);
    } else if (cmp > 0) {
        h->r = RBT_insert(h->r, key, val);
    } else /*cmp == 0*/ {
        // Updating
        h->value = RBT_insert(h->value, val, NULL);
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
    free(h->value);
    free(h);
    h = NULL;
}

// Only frees keys
void RBT_destroy(RBT *h) {
    RBT_runOnAll_postOrder(h, RBT_freeFunction);
}
