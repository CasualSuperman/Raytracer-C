#ifndef LIST_H
#define LIST_H

#include "object.h"

typedef struct {
    obj_t *head;
    obj_t *tail;
} list_t;

list_t* init_list(void);
void add_list(list_t *, obj_t *);
void free_list(list_t *);

#endif
