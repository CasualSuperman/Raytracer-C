#include <stdio.h>
#include <stdlib.h>

// Malloc size_t bytes. Exit with stack trace on failure.
void *Malloc(size_t size) {
    void *array[10];
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("malloc of %lu bytes failed.\n", size);
        backtrace_symbols_fd(array, 10, stderr);
        exit(1);
    }
    return ptr;
}

// Calloc num*size_t bytes. Exit with stack trace on failure.
void *Calloc(size_t num, size_t size) {
    void *array[10];
    void *ptr = calloc(num, size);
    if (ptr == NULL) {
        printf("calloc of %lu*%lu bytes failed.\n", num, size);
        backtrace_symbols_fd(array, 10, stderr);
        exit(1);
    }
    return ptr;
}

// Realloc size_t bytes and copy ptr contents. Exit with stack trace on failure.
void *Realloc(void *ptr, size_t size) {
    void *array[10];
    void *new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        printf("realloc of %lu bytes failed.\n", size);
        backtrace_symbols_fd(array, 10, stderr);
        exit(1);
    }
    return new_ptr;
}
