#include "../lib/page.h"

Page *initializePage(char *pageName, float powerRank, int nOutLinks, Page **listPages) {
    Page *page = malloc(sizeof(Page));
    page->pageName = strdup(pageName);
    page->powerRank = powerRank;
    page->nOutLinks = nOutLinks;
    page->listPages = listPages;
    return page;
}

void copyPage(void *pageDest, void *pageSrc) {
    Page *castedDestPage = (Page *)pageDest;
    Page *castedSrcPage = (Page *)pageSrc;
    castedDestPage->listPages = castedSrcPage->listPages;
    castedDestPage->powerRank = castedSrcPage->powerRank;
    castedDestPage->nOutLinks = castedSrcPage->nOutLinks;
}

void freePage(Page *page, int freeLinkedPages) {
    free(page->pageName);
    if (freeLinkedPages) {
        free(page->listPages);
    }
    free(page);
}

void printPage(Page *page) {
    printf("##############printPage################\n");
    printf("O nome da página é ");
    puts(page->pageName);
    printf("O page rank é: %lf\n", page->powerRank);
    printf("O número de links saindo da página é %d\n", page->nOutLinks);
    for (int i = 0; i < page->nOutLinks; i++) {
        printf(
            "O link %d é a página %s\n",
            i, (page->listPages[i])->pageName);
    }
    printf("##############printPage################\n");
}
