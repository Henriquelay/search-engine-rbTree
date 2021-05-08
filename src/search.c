#include "../lib/search.h"


//só pra passar algo pro callback
void* placeholder(RBT *node, void *val){
    return val;
}


RBT* RBT_update_on_hit(RBT *h, RBT* l, RBT* new_tree){
    if(RBT_search(l, h->key)){
        new_tree = RBT_insert(new_tree, h->key, h->value, placeholder);
    }
    return new_tree;
}


RBT* intersection_recursion_step(RBT* h, RBT* l, RBT* aux_tree){
    if (h != NULL){
        aux_tree = RBT_update_on_hit(h, l, aux_tree);
        if(h->l != NULL){
            intersection_recursion_step(h->l, l, aux_tree);

        }
        if(h->r != NULL){
            intersection_recursion_step(h->r, l, aux_tree);
        }
    }
    return aux_tree;
}


RBT* get_RBT_interesction(RBT *h, RBT* l){

    RBT* aux_tree = NULL;
    aux_tree = intersection_recursion_step(h, l, aux_tree);
    return aux_tree;
}


void printa_key_RBT(RBT* node){
    printf("Chave é %s\n", node->key);
}


RBT* start_intersection_tree(RBT* symbol_table, char* palavra){
    RBT* page_tree = RBT_search(symbol_table, palavra)->value;
    page_tree = get_RBT_interesction(page_tree, page_tree);
    return page_tree;
}


void search(char* line, RBT* symbol_table){
    const char delim[2] = " ";
    char* seach_keyword = strtok(line, delim);
    RBT* page_intersection_tree = start_intersection_tree(symbol_table, seach_keyword);
    seach_keyword = strtok(NULL, delim);
    while(seach_keyword != NULL){
        RBT* page_tree = RBT_search(symbol_table, seach_keyword)->value;
        RBT* page_tree_aux = get_RBT_interesction(page_intersection_tree, page_tree);
        RBT_destroy(page_intersection_tree);
        page_intersection_tree = page_tree_aux;

        seach_keyword = strtok(NULL, delim);
    }
    RBT_runOnAll_inOrder(page_intersection_tree, printa_key_RBT);
    RBT_destroy(page_intersection_tree);

}