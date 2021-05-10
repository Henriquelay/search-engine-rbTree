#ifndef PAGERANK_H_
#define PAGERANK_H_

#include<stdio.h>
#include<math.h>
#include"./rbTree.h"
#include"page.h"
#include"list.h"

/*
    Biblioteca pageRank.h
    Contem a implementacao do calculo do page rank
*/

void calculate_pageRank(RBT *pages);

#endif
