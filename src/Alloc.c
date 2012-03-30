#include <stdio.h>
#include <stdlib.h>

#include "Alloc.h"
#include "exit.h"
#include "log.h"

#ifdef DEBUG_MEMORY
static int allocated = 0;
#endif

// Malloc size_t bytes. Exit on failure.
void* Malloc(size_t size) {
    void *ptr = malloc(size);

    if (ptr == NULL) {
        say("malloc of %zu bytes failed.", size);
        exit(EXIT_FAILED_ALLOC);
    }

#ifdef DEBUG_MEMORY
	say("Allocated memory. Allocated objects - %d", ++allocated);
#endif

	return ptr;
}

// Calloc num*size_t bytes. Exit on failure.
void* Calloc(size_t num, size_t size) {
    void *ptr = calloc(num, size);

    if (ptr == NULL) {
        say("calloc of %zu*%zu bytes failed.", num, size);
        exit(EXIT_FAILED_ALLOC);
    }

#ifdef DEBUG_MEMORY
	say("Allocated memory. Allocated objects - %d", ++allocated);
#endif

	return ptr;
}

// Realloc size_t bytes and copy ptr contents. Exit on failure.
void* Realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size);

    if (new_ptr == NULL) {
        say("realloc of %zu bytes failed.", size);
        exit(EXIT_FAILED_ALLOC);
    }

#ifdef DEBUG_MEMORY
	say("Allocated memory. Allocated objects - %d", ++allocated);
#endif

	return new_ptr;
}

inline void Free(void *ptr) {
#ifdef DEBUG_MEMORY
	say("Freed memory. Allocated objects - %d", --allocated);
#endif
	free(ptr);
}
