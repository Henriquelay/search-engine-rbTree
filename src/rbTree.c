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
    RBT *new = malloc(sizeof(RBT));
    new->key = strdup(val);
    new->value = NULL;
    new->color = color;
    new->l = new->r = NULL;
    return new;
}

RBT *create_node(char *key, void *val, char color) {
    RBT *new = malloc(sizeof(RBT));
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
        h->value = val;
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

void RBT_free(RBT *h) {
    if (h == NULL) {
        return;
    }
    RBT_free(h->l);
    RBT_free(h->r);
    free(h->key);
    RBT_free(h->value);
    free(h);
}

void RBT_runOnAll_inOrder(RBT *h, void (*visit)(RBT *)) {
    if (h->l != NULL) {
        RBT_runOnAll_inOrder(h->l, visit);
    }
    visit(h);
    if (h->r != NULL) {
        RBT_runOnAll_inOrder(h->r, visit);
    }
}

void RBT_print(RBT *h) {
    printf("Node: %s : ", h->key);
    printf("%s\n", (char*) h->value);
}
