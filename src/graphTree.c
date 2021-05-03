#include "../lib/graphTree.h"

GraphNode *searchGT(GraphNode *n, char *key) {
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

int is_redGT(GraphNode *x) {
    if (x == NULL)
        return 0;
    return x->color; //RED == 1
}

GraphNode *rotate_leftGT(GraphNode *h) {
    GraphNode *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = 1; //vermelho
    return x;
}

GraphNode *rotate_rightGT(GraphNode *h) {
    GraphNode *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = 1;
    return x;
}

void flip_colorsGT(GraphNode *h) {
    h->color = 1;
    h->l->color = 0;
    h->r->color = 0;
}

GraphNode *create_nodeGT(char *key, void *data, int color) {
    GraphNode *new = malloc(sizeof(GraphNode));
    new->key = strdup(key);
    new->data = data;
    new->color = color;
    new->l = new->r = NULL;
    return new;
}

GraphNode *GraphNode_insert(
    GraphNode *h, char *key, void *data,
    int update, void (*update_func)(void *, void *)) {
    // Insert at bottom and color it red.
    if (h == NULL) {
        return create_nodeGT(key, data, 1);
    }
    int cmp = strcmp(key, h->key);
    if (cmp < 0) {
        h->l = GraphNode_insert(h->l, key, data, update, update_func);
    } else if (cmp > 0) {
        h->r = GraphNode_insert(h->r, key, data, update, update_func);
    } else if (update) {
        update_func(h->data, data);
    }
    // Lean left.
    if (is_redGT(h->r) && !is_redGT(h->l)) {
        h = rotate_leftGT(h);
    }
    // Balance 4-node.
    if (is_redGT(h->l) && is_redGT(h->l->l)) {
        h = rotate_rightGT(h);
    }
    // Split 4-node.
    if (is_redGT(h->l) && is_redGT(h->r)) {
        flip_colorsGT(h);
    }
    return h;
}

void GraphNode_free(GraphNode *h) {
    if (h == NULL) {
        return;
    }
    GraphNode_free(h->l);
    GraphNode_free(h->r);
    free(h->key);
    free(h);
}
