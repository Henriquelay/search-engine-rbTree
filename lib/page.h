#ifndef _PAGE_H_
#define _PAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct page Page;
struct page {
    char *pageName;
    float powerRank;
    int nOutLinks;
    Page **listPages;
};

Page *Page_init(char *pageName, float powerRank, int nOutLinks, Page **listPages);

void Page_copy(void *pageDest, void *pageSrc);

void Page_destroy(Page *page, int freeLinkedPages);

void Page_print(Page *page);

#endif
