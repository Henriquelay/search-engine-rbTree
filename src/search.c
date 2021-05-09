#include "../lib/search.h"

void printa_key_RBT(RBT* node){
    printf("Chave é %s\n", node->key);
}

//só pra passar algo pro callback
void* placeholder(RBT *node, void *val){
    return val;
}


RBT* RBT_update_on_hit(RBT *smaller_tree, RBT* bigger_tree, RBT* new_tree){
    RBT* test;
    if((test = RBT_search(bigger_tree, smaller_tree->key))){
        new_tree = RBT_insert(new_tree, smaller_tree->key, smaller_tree->value, placeholder);
    }
    return new_tree;
}


RBT* intersection_recursion_step(RBT* smaller_tree, RBT* bigger_tree, RBT* resulting_tree){
    if(smaller_tree != NULL){
        resulting_tree = RBT_update_on_hit(smaller_tree, bigger_tree, resulting_tree);
        resulting_tree = intersection_recursion_step(smaller_tree->l, bigger_tree, resulting_tree);
        resulting_tree = intersection_recursion_step(smaller_tree->r, bigger_tree, resulting_tree); 
    }
    return resulting_tree;
}


RBT* get_RBT_interesction(RBT *smaller_tree, RBT* bigger_tree){

    RBT* resulting_tree = NULL;
    resulting_tree = intersection_recursion_step(smaller_tree, bigger_tree, resulting_tree);
    return resulting_tree;
}




RBT* start_intersection_tree(RBT* symbol_table, char* palavra){
    RBT* page_tree = RBT_search(symbol_table, palavra)->value;
    page_tree = get_RBT_interesction(page_tree, page_tree);
    return page_tree;
}

// Symbol table key: string, 
// Symbol table val: RBT* (páginas [key: string, val: null])
void search(char* line, RBT* symbol_table){
    if(!line){return;}
    const char delim[2] = " ";
    char* search_keyword = strtok(line, delim);
    RBT* page_intersection_tree = NULL;
    while(search_keyword != NULL && RBT_search(symbol_table,search_keyword) == NULL){
        search_keyword = strtok(NULL, delim);
    }
    if(search_keyword != NULL){
        page_intersection_tree = start_intersection_tree(symbol_table, search_keyword);
        search_keyword = strtok(NULL, delim);
    }

    while(search_keyword != NULL && RBT_search(symbol_table, search_keyword) != NULL){
        puts("teste");
        RBT* page_tree = RBT_search(symbol_table, search_keyword)->value;
        RBT* page_tree_aux = get_RBT_interesction(page_intersection_tree, page_tree);
        RBT_destroy(page_intersection_tree);
        page_intersection_tree = page_tree_aux;

        search_keyword = strtok(NULL, delim);
    }
    if(page_intersection_tree != NULL){
    printf("#### DEBUG ####\n");
    RBT_runOnAll_inOrder(page_intersection_tree, printa_key_RBT);
    RBT_destroy(page_intersection_tree);
    }

}


void print_output(RBT* symbol_table){
    char* lineptr = NULL;
    size_t line_buffer_size = 0;
    ssize_t nCharacterRead;
    while((nCharacterRead = getline(&lineptr, &line_buffer_size, stdin)) != -1){
        printf("NUMERO LIDOS %ld\n", nCharacterRead);
        if (lineptr[nCharacterRead - 1] == '\n') {
            lineptr[nCharacterRead - 1] = '\0';
        }
        if(!(*lineptr)){continue;}
        // puts(lineptr);
        search(lineptr, symbol_table);
    }
    free(lineptr);

    
}
