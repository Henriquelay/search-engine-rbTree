#include "../lib/list.h"

list_t *list_init() {
    list_t *newList = (list_t *)malloc(sizeof(list_t));
    if (newList == NULL) {
        perror("Error creating new list. Exiting");
        exit(1);
    }
    newList->head = NULL;
    newList->tail = NULL;
    newList->count = 0;

    return newList;
}

char list_isEmpty(list_t *list) {
    return list->head == NULL;
}

void list_push(list_t *list, void *item) {
    if (item == NULL) {
        return;
    }
    linked_node_t *newNode = (linked_node_t *)malloc(sizeof(linked_node_t));
    if (newNode == NULL) {
        perror("Allocation error: Node couldn't be created. Exiting.");
        exit(1);
    }

    list->count++;

    newNode->value = item;
    newNode->previous = NULL;
    // List is not empty
    if (list->head != NULL) {
        list->head->previous = newNode;
    }
    newNode->next = list->head;
    list->head = newNode;
    if (list->tail == NULL) {
        list->tail = newNode;
    }
}

void *list_pop(list_t *list) {
    if (list->head == NULL) {
        return NULL;
    }

    list->count--;

    void *holder = list->head->value;
    linked_node_t *destroyMe = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    } else {
        list->head->previous = NULL;
    }
    free(destroyMe);
    return holder;
}

void list_enqueue(list_t *list, void *item) {
    if (item == NULL) {
        return;
    }
    linked_node_t *newNode = (linked_node_t *)malloc(sizeof(linked_node_t));
    if (newNode == NULL) {
        perror("Allocation error: Node couldn't be created. Exiting.");
        exit(1);
    }

    list->count++;

    newNode->value = item;
    newNode->next = NULL;
    newNode->previous = list->tail;
    if (newNode->previous != NULL) {
        newNode->previous->next = newNode;
    }
    list->tail = newNode;
    if (list->head == NULL) {
        list->head = newNode;
    }
}

void *list_dequeue(list_t *list) {
    return list_pop(list);
}

void list_print(list_t *list, const char *format) {
    for (linked_node_t *current = list->head; current != NULL; current = current->next) {
        printf(format, current->value);
    }
}

void pointerThingy(linked_node_t *node) {
    if (node != NULL) {
        if (node->next != NULL) {
            node->next->previous = node->previous;
        }
        if (node->previous != NULL) {
            node->previous->next = node->next;
        }
    }
}

void list_destroy(list_t *list, char freeInnerValue) {
    if (list != NULL) {
        while (list->head != NULL) {
            linked_node_t *freeMe = list->head;
            list->head = list->head->next;
            if (freeInnerValue > 0) {
                free(freeMe->value);
            }
            free(freeMe);
        }
        free(list);
    }
}

void list_runOnAll(list_t *list, void (*visit)(linked_node_t *)) {
    if (list != NULL) {
        linked_node_t *useMe = list->head;
        while (useMe != NULL) {
            linked_node_t *useMeNext = useMe->next;
            visit(useMe);
            useMe = useMeNext;
        }
    }
}
