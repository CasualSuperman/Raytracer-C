#ifndef LIST_H
#define LIST_H

typedef struct link_type {
    void *item;
    struct link_type *next;
} link_t;

typedef struct list_type {
    link_t *head;
    link_t *tail;
} list_t;

#endif
