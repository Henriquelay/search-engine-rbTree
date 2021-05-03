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

Page *initializePage(char *pageName, float powerRank, int nOutLinks, Page **listPages);

void copyPage(void *pageDest, void *pageSrc);

void freePage(Page *page, int freeLinkedPages);

void printPage(Page *page);

#endif
