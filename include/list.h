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

list_t *list_init(void);
void list_add(list_t *, void *);
void list_del(list_t *);

#endif
