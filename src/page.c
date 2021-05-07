#include "../lib/page.h"

Page *Page_init(char *pageName) {
    Page *page = malloc(sizeof(Page));
    if (page == NULL) {
        perror("Page allocation failed");
        exit(EXIT_FAILURE);
    }
    page->pageName = strdup(pageName);
    page->pageRankPrev = -1;
    page->pageRank = -1;
    page->nOutLinks = 0;
    page->outPages = NULL;
    page->nInLinks = 0;
    page->inPages = NULL;
    return page;
}

void Page_copy(void *pageDest, void *pageSrc) {
    Page *castedDestPage = (Page *)pageDest;
    Page *castedSrcPage = (Page *)pageSrc;
    castedDestPage->outPages = castedSrcPage->outPages;
    castedDestPage->pageRank = castedSrcPage->pageRank;
    castedDestPage->nOutLinks = castedSrcPage->nOutLinks;
}

void Page_destroy(Page *page, int freeLinkedPages) {
    free(page->pageName);
    if (freeLinkedPages) {
        free(page->outPages);
    }
    free(page);
}

void Page_print(Page *page) {
    if (page == NULL) {
        puts("NULL");
        return;
    }
    printf("Name: '%s'\n", page->pageName);
    printf("PR: %lf\n", page->pageRank);
    printf("Previous PR: %lf\n", page->pageRankPrev);
    printf("Link out #: %d\n", page->nOutLinks);
    if (page->outPages != NULL) {
        for (unsigned int i = 0; i < page->nOutLinks; i++) {
            printf(
                "Link %d points to '%s'\n",
                i, page->outPages[i] != NULL ? page->outPages[i]->pageName : "NULL");
        }
    }
    printf("Link in #: %d\n", page->nInLinks);
    if (page->inPages != NULL) {
        for (unsigned int i = 0; i < page->nInLinks; i++) {
            printf(
                "Link %d points to '%s'\n",
                i, page->inPages[i] != NULL ? page->inPages[i]->pageName : "NULL");
        }
    }
    printf("---\n");
}
