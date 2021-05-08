#include "../lib/search.h"


//só pra passar algo pro callback
void* placeholder(RBT *node, void *val){
    return val;
}


void RBT_free_pages_node_copia(RBT *h) {
    RBT_destroy(h);
}


RBT* RBT_update_on_hit(RBT *h, RBT* l, RBT* new_tree){
    if(RBT_search(l, h->key)){
        new_tree = RBT_insert(new_tree, h->key, h->value, placeholder);
    }
    return new_tree;
}


RBT* intersection_recursion_step(RBT* h, RBT* l, RBT* aux_tree){
    if (h != NULL){
        printf("vou entrar\n");
        aux_tree = RBT_update_on_hit(h, l, aux_tree);
        printf("sai dela\n");
        if(h->l != NULL){
            printf("teste\n");
            intersection_recursion_step(h->l, l, aux_tree);

        }
        if(h->r != NULL){
            printf("teste\n");
            intersection_recursion_step(h->r, l, aux_tree);
        }
    }
    printf("Grafos com boeres\n");
    return aux_tree;
}

RBT* get_RBT_interesction(RBT *h, RBT* l){

    RBT* aux_tree = NULL;
    aux_tree = intersection_recursion_step(h, l, aux_tree);
    //RBT_runOnAll_inOrder(h, RBT_free_pages_node_copia);
    return aux_tree;
}


void printa_key_RBT(RBT* node){
    printf("Chave é %s\n", node->key);
}


int page_is_equal(RBT* node_page1, RBT* node_page2){
    return(!strcmp(node_page1->key, node_page2->key));
}


void list_printao(list_t *list, const char *format) {
    for (linked_node_t *current = list->head; current != NULL; current = current->next) {
        printf(format, current->value);
    }
}

RBT* start_intersection_tree(RBT* symbol_table, char* palavra){
    RBT* palavra_suporte_node = RBT_search(symbol_table, palavra);
    RBT* pages_with_palavra_suporte = (RBT *)(palavra_suporte_node->value);
    pages_with_palavra_suporte = get_RBT_interesction(pages_with_palavra_suporte, pages_with_palavra_suporte);
    return pages_with_palavra_suporte;
}


void search(char* line, RBT* symbol_table){
    const char delim[2] = " ";
    char* palavra = strtok(line, delim);
    RBT* intersection_tree = start_intersection_tree(symbol_table, palavra);
    palavra = strtok(NULL, delim);
    while(palavra != NULL){
        RBT* palavra_node = RBT_search(symbol_table, palavra);
        RBT* pages_with_palavra = (RBT *)(palavra_node->value);
        RBT* aux_tree_pointer = get_RBT_interesction(intersection_tree, pages_with_palavra);
        RBT_destroy(intersection_tree);
        intersection_tree = aux_tree_pointer;

        palavra = strtok(NULL, delim);
    }
    RBT_runOnAll_inOrder(intersection_tree, printa_key_RBT);
    RBT_destroy(intersection_tree);

}