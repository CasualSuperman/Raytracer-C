#include <stdio.h>
#include <stdlib.h>

#include "../include/Alloc.h"

static const int STACK_SIZE = 10;

// Malloc size_t bytes. Exit with stack trace on failure.
void *Malloc(size_t size) {
//    void *array[STACK_SIZE];
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "malloc of %lu bytes failed.\n", size);
//        backtrace_symbols(array, STACK_SIZE);
//        backtrace_symbols_fd(array, STACK_SIZE, stderr);
        exit(1);
    }
    return ptr;
}

// Calloc num*size_t bytes. Exit with stack trace on failure.
void *Calloc(size_t num, size_t size) {
//    void *array[STACK_SIZE];
    void *ptr = calloc(num, size);
    if (ptr == NULL) {
        fprintf(stderr, "calloc of %lu*%lu bytes failed.\n", num, size);
//        backtrace_symbols(array, STACK_SIZE);
//        backtrace_symbols_fd(array, STACK_SIZE, stderr);
        exit(1);
    }
    return ptr;
}

// Realloc size_t bytes and copy ptr contents. Exit with stack trace on failure.
void *Realloc(void *ptr, size_t size) {
//    void *array[STACK_SIZE];
    void *new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        fprintf(stderr, "realloc of %lu bytes failed.\n", size);
//        backtrace_symbols(array, STACK_SIZE);
//        backtrace_symbols_fd(array, STACK_SIZE, stderr);
//
        exit(1);
    }
    return new_ptr;
}
