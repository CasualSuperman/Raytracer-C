#include <stdio.h>

#include "Alloc.h"
#include "list.h"

list_t *list_init(void) {
    list_t *list = Malloc(sizeof(list));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_add(list_t *list, void *entity) {
    if (list == NULL) {
        fprintf(stderr, "Warning: Tried to add to a NULL list.");
        return;
    }

    link_t *node = Malloc(sizeof(link_t));
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    node->item = entity;
}

void list_del(list_t *list) {
    if (list == NULL) {
        fprintf(stderr, "Warning: Tried to add to a NULL list.");
        return;
    }

    link_t *node = list->head;
    link_t *next = NULL;

    while (node != NULL) {
        next = node->next;
        free(node->item);
        free(node);
        node = next;
    }
    free(list);
}