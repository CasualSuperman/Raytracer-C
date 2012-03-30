#include <stdio.h>

#include "Alloc.h"
#include "list.h"
#include "log.h"

#include "object.h"

list_t* init_list(void) {
    list_t *list = Malloc(sizeof(list_t));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void add_list(list_t *list, obj_t *entity) {
    if (list == NULL) {
        say("Warning: Tried to add to a NULL list.");
        return;
    }

    if (list->head == NULL) {
        list->head = entity;
        list->tail = entity;
    } else {
        list->tail->next = entity;
        list->tail       = entity;
    }
}

void free_list(list_t *list) {
	obj_t *node = NULL;
	obj_t *next = NULL;

    if (list == NULL) {
        say("Warning: Tried to free a NULL list.");
        return;
    }

	node = list->head;

    while (node != NULL) {
        next = node->next;
        free_object(node);
        node = next;
    }

    Free(list);
}
