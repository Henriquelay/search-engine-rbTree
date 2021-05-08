#include"../lib/pageRank.h"
#define ALPHA 0.85
#define PR_LIMIT 0.000001

list_t* convert_listFromRBT(RBT *h, list_t *pagesList)
{
    if (h != NULL) {
        convert_listFromRBT(h->l, pagesList);
        list_enqueue(pagesList, h->value);
        convert_listFromRBT(h->r, pagesList);
    }
    return pagesList;
}

void calculate_pageRank(RBT *pages) {
    //Converte a arvore rb em uma lista, mais facil de acessar sequencialmente ao inves de usar 
    //Caminhamento em ordem o tempo todo ou buscar na árvore.
    list_t *pagesList = list_init();
    convert_listFromRBT(pages, pagesList);
    linked_node_t *currentPage = NULL;

    //Inicialização dos valores padrao do page rank como 1/n para todas as paginas
    for(currentPage = pagesList->head; currentPage != NULL; currentPage = currentPage->next) {
        ((Page *)currentPage->value)->pageRank = 1/pagesList->count;
        ((Page *)currentPage->value)->pageRankPrev = ((Page *)currentPage->value)->pageRank;
    }
    
    double currentLimit = 1;
    double sum;
    linked_node_t *currentInPage = NULL;
    //Executa enquanto o somatorio E for maior que a constante definida arbitrariamente
    while(currentLimit > PR_LIMIT) {
        //Calcula o PR da iteracao atual de todas as paginas
        for(currentPage = pagesList->head; currentPage != NULL; currentPage = currentPage->next) {
            sum = 0;
            int outPagesCount = ((Page *)currentPage->value)->outPagesCount;
            //Calcula o somatorio de todas as paginas que tem link chegando na pagina atual
            for(currentInPage = ((Page *)currentPage->value)->inPages->head; currentInPage != NULL; currentInPage = currentInPage->next) {
                sum += ((Page *)currentInPage->value)->pageRankPrev/((Page *)currentInPage->value)->outPagesCount;
            }

            //Se |out(i)| != 0 ou se |out(i)| = 0
            if(outPagesCount != 0) {
                ((Page *)currentPage->value)->pageRank = ((1-ALPHA)/pagesList->count) + (sum * ALPHA);
            }
            else {
                ((Page *)currentPage->value)->pageRank = ((1-ALPHA)/pagesList->count) + ALPHA * ((Page *)currentPage->value)->pageRankPrev + (sum * ALPHA);
            }
        }

        //Calcula o E da iteracao atual
        currentLimit = 0;
        for(currentPage = pagesList->head; currentPage != NULL; currentPage = currentPage->next) {
            currentLimit += fabs(((Page *)currentPage->value)->pageRank - ((Page *)currentPage->value)->pageRankPrev);
            //Depois de utilzar o pageRank e o pageRankPrev para o calculo do E atualiza o page rank anterior sendo o atual para o proximo calculo
            ((Page *)currentPage->value)->pageRankPrev = ((Page *)currentPage->value)->pageRank;
        }
        currentLimit *= 1/(double)pagesList->count;
    }

    list_destroy(pagesList, 0);
}
