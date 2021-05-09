#ifndef _PAGE_H_
#define _PAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct page Page;
struct page {
    char *name;
    float pageRankPrev;
    float pageRank;

    int outPagesCount;
    Page **outPages;

    list_t *inPages;
};

Page *Page_init(char *pageName);

void Page_copy(void *pageDest, void *pageSrc);

void Page_destroy(Page *page);

void Page_print(Page *page);

int Page_cmp(const void*, const void *);

#endif
