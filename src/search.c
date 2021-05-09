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
    RBT* search_result = RBT_search(symbol_table, palavra);
    if(!search_result){
        return NULL;
    }
    RBT* page_tree = search_result->value;
    page_tree = get_RBT_interesction(page_tree, page_tree);
    return page_tree;
}

// Symbol table key: string, 
// Symbol table val: RBT* (páginas [key: string, val: null])

RBT* search(char* line, RBT* symbol_table){
    if(!line){return NULL;}
    const char delim[2] = " ";
    char* search_keyword = strtok(line, delim);
    RBT* page_intersection_tree = NULL;

    if(search_keyword != NULL){
        page_intersection_tree = start_intersection_tree(symbol_table, search_keyword);
        if(!page_intersection_tree){
            return NULL;
        }
        search_keyword = strtok(NULL, delim);
    }

    while(search_keyword != NULL){
        RBT* search_result = RBT_search(symbol_table, search_keyword);
        if(!search_result){
            RBT_destroy(page_intersection_tree);
            return NULL;
        }
        RBT* page_tree = search_result->value;
        RBT* page_tree_aux = get_RBT_interesction(page_intersection_tree, page_tree);
        RBT_destroy(page_intersection_tree);
        if(!page_tree_aux){
            return NULL;
        }
        page_intersection_tree = page_tree_aux;

        search_keyword = strtok(NULL, delim);
    }
    return page_intersection_tree;

}


void print_output(RBT* symbol_table, RBT* page_graph){
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
        RBT* page_intersection_tree = search(lineptr, symbol_table);
        if(page_intersection_tree){
            RBT_runOnAll_inOrder(page_intersection_tree, printa_key_RBT);
            int array_size = -1;
            Page** page_array = RBT_value_to_array(page_intersection_tree, &array_size, page_graph);
            printf("Funciona pf nunca te pedi nada\n");
            printf("array_size: %d\n", array_size);
            for(int i=0; i<array_size; i++){
                printf("A página %d do array tem nome %s\n", i, page_array[i]->name);
            }
            RBT_destroy(page_intersection_tree);
        }
    }
    free(lineptr);

    
}
