#ifndef LIST_H
#define LIST_H

#include "object.h"

/**
 * list_t - A struct for use with a linked list. The type stored, obj_t, has a
 * next field, which works as the links in the list.
 */
typedef struct {
    obj_t *head;
    obj_t *tail;
} list_t;

/**
 * init_list - Allocates a list_t on the heap, initializes its values, and
 * returns it.
 *
 * @return An allocated list.
 */
list_t* init_list(void);

/**
 * add_list - Adds an obj_t to the end of the given list.
 *
 * @param The list to add to.
 * @param The item to add.
 */
void add_list(list_t *, obj_t *);

/**
 * free_list - Takes a list, and frees each item in it, then frees the list
 * itself.
 *
 * @param The list to free.
 */
void free_list(list_t *);

#endif
