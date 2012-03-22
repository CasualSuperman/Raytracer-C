#include <stdio.h>
#include <stdlib.h>

#include "Alloc.h"
#include "exit.h"

// Malloc size_t bytes. Exit on failure.
void* Malloc(size_t size) {
    void *ptr = malloc(size);

    if (ptr == NULL) {
        /*@i@*/fprintf(stderr, "malloc of %zu bytes failed.\n", size);
        exit(EXIT_FAILED_ALLOC);
    }

    return ptr;
}

// Calloc num*size_t bytes. Exit on failure.
void* Calloc(size_t num, size_t size) {
    void *ptr = calloc(num, size);

    if (ptr == NULL) {
        /*@i@*/fprintf(stderr, "calloc of %zu*%zu bytes failed.\n", num, size);
        exit(EXIT_FAILED_ALLOC);
    }

    return ptr;
}

// Realloc size_t bytes and copy ptr contents. Exit on failure.
void* Realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size);

    if (new_ptr == NULL) {
        /*@i@*/fprintf(stderr, "realloc of %zu bytes failed.\n", size);
        exit(EXIT_FAILED_ALLOC);
    }

    return new_ptr;
}
