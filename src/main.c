#include "../lib/reader.h"
#include "../lib/search.h"
#include "../lib/pageRank.h"
#include "../lib/util.h"
#include <stdio.h>

int main(int argc, char **argv){
    char *fileSource = argv[1];
    RBT *wordsTree = NULL;

    // Leitura dos arquivos 
    RBT *pagesTree = readData(fileSource, &wordsTree);

    // Leitura dos links entre as paginas
    readGraph(fileSource, pagesTree);

    // Calculo do Page Rank
    calculate_pageRank(pagesTree);
    
    // Pesquisa e resultado
    print_output(wordsTree, pagesTree);

    // Liberacao as arvores
    RBT_freeReverseIndexTree(wordsTree);
    RBT_freePagesTree(pagesTree);
}
