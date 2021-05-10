#ifndef _UTIL_H_
#define _UTIL_H_

#include<stdio.h>
#include<math.h>
#include"./rbTree.h"
#include "../lib/util.h"
#include"page.h"

/*
    Biblioteca util.h
    Contem implementacao de funcoes uteis para a manipulacao das
    RBTs.
*/

void RBT_printReverseIndexTreeNodeValue(RBT *h);

void RBT_printReverseIndexTreeNode(RBT *h);

void RBT_freeReverseIndexNode(RBT *h);

void RBT_freeReverseIndexTree(RBT *tree);

void RBT_freePagesTreeNode(RBT *h);

void RBT_freePagesTree(RBT *h);

void RBT_printPagesTreeNode(RBT *h);

#endif