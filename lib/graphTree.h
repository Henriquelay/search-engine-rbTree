#ifndef GraphNodeREE_H_
#define GraphNodeREE_H_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "page.h"

typedef struct graphNode GraphNode;

struct graphNode {
    char* key;
    void* data;
    int color;
    GraphNode *l, *r;
};

GraphNode* searchGT(GraphNode *n, char* key);
GraphNode* rotate_leftGT(GraphNode *h);
GraphNode* rotate_rightGT(GraphNode *h);
GraphNode* GraphNode_insert(
    GraphNode *h, char* key, void* data,
    int update, void (*update_func)(void*, void*));
void flip_colorsGT(GraphNode *h);
void GraphNode_free(GraphNode *h);

//nossas

#endif // !GraphNodeREE_H_
