#include "../lib/page.h"

Page *Page_init(char *pageName, float powerRank, int nOutLinks, Page **listPages) {
    Page *page = malloc(sizeof(Page));
    page->pageName = strdup(pageName);
    page->powerRank = powerRank;
    page->nOutLinks = nOutLinks;
    page->listPages = listPages;
    return page;
}

void Page_copy(void *pageDest, void *pageSrc) {
    Page *castedDestPage = (Page *)pageDest;
    Page *castedSrcPage = (Page *)pageSrc;
    castedDestPage->listPages = castedSrcPage->listPages;
    castedDestPage->powerRank = castedSrcPage->powerRank;
    castedDestPage->nOutLinks = castedSrcPage->nOutLinks;
}

void Page_destroy(Page *page, int freeLinkedPages) {
    free(page->pageName);
    if (freeLinkedPages) {
        free(page->listPages);
    }
    free(page);
}

void Page_print(Page *page) {
    if (page == NULL) {
        puts("NULL");
        return;
    }
    printf("printPage\n");
    printf("Name: '%s'\n", page->pageName);
    puts(page->pageName);
    printf("Page Rank: %lf\n", page->powerRank);
    printf("O num link out: %d\n", page->nOutLinks);
    for (int i = 0; i < page->nOutLinks; i++) {
        printf(
            "Link %d points to '%s'\n",
            i, page->listPages[i] ? page->listPages[i]->pageName : "NULL");
    }
    printf("---\n");
}
