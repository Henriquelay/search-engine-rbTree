#include "../lib/page.h"

Page *Page_init(char *pageName) {
    Page *page = malloc(sizeof(Page));
    if (page == NULL) {
        perror("Page allocation failed");
        exit(EXIT_FAILURE);
    }
    page->name = strdup(pageName);
    page->pageRankPrev = -1;
    page->pageRank = -1;
    page->outPagesCount = 0;
    page->outPages = NULL;
    page->inPages = list_init();
    return page;
}

void Page_copy(void *pageDest, void *pageSrc) {
    Page *castedDestPage = (Page *)pageDest;
    Page *castedSrcPage = (Page *)pageSrc;
    castedDestPage->outPages = castedSrcPage->outPages;
    castedDestPage->pageRank = castedSrcPage->pageRank;
    castedDestPage->outPagesCount = castedSrcPage->outPagesCount;
}

void Page_destroy(Page *page) {
    free(page->name);
    free(page->outPages);
    list_destroy(page->inPages, 0);
    free(page);
}

void Page_printNameCallBack(linked_node_t *node) {
    printf("'%s' ", (char *)((Page *)node->value)->name);
}

void Page_print(Page *page) {
    if (page == NULL) {
        puts("NULL");
        return;
    }
    printf("Name: '%s'\n", page->name);
    printf("PR: %lf\n", page->pageRank);
    printf("Previous PR: %lf\n", page->pageRankPrev);
    printf("Link out #: %d\n", page->outPagesCount);
    if (page->outPages != NULL) {
        for (unsigned int i = 0; i < page->outPagesCount; i++) {
            printf(
                "OutLink %d points to '%s'\n",
                i, page->outPages[i] != NULL ? page->outPages[i]->name : "NULL");
        }
    }
    printf("Link in #: %d\n", page->inPages->count);
    if (page->inPages != NULL) {
        list_runOnAll(page->inPages, Page_printNameCallBack);
        puts("");
    }
    printf("---\n");
}


int Page_cmp(const void* page1, const void *page2){
    Page* page1_deref = *(Page**)page1;
    Page* page2_deref = *(Page**)page2;
    double rank_result = (page1_deref->pageRank) - (page2_deref->pageRank);
    if((rank_result = page1_deref->pageRank - page2_deref->pageRank) != 0){
        return rank_result;
    }
    return strcmp(page1_deref->name, page2_deref->name);
}