#ifndef ALLOC_H
#define ALLOC_H

#include <stdlib.h>

/**
 * Malloc - Takes a size_t representing the number of bytes to allocate.  Exits
 * if the allocation fails, otherwise returns a pointer to the allocated
 * memory.
 *
 * @param The number of bytes to allocate.
 *
 * @return The address of the allocated memory.
 */
void* Malloc(size_t size);

/**
 * Calloc - Takes a size_t of the number of elements, and a size_t of the
 * number of elements to allocate, allocates and zeroes them, and returns a
 * pointer to the allocated memory. Exits on failure.
 *
 * @param The number of elements to allocate.
 * @param The size of each element.
 *
 * @return The address of the allocated memory.
 */
void* Calloc(size_t num, size_t size);

/**
 * Realloc - Takes an already allocated pointer, and a size_t representing the
 * new size of the memory we wish to allocate. Allocates the new memory and
 * copies over the old contents from prt to the new memory. Returns the pointer
 * to the allocated memory, and exits on failure.
 *
 * @param The pointer we wish to copy to the newly allocated memory.
 * @param The size of the new block to allocate.
 *
 * @return The address of the allocated memory.
 */
void* Realloc(void *, size_t);

/**
 * Free - A wrapper function for free that is used for debugging purposes.
 *
 * @param The pointer to memory we want to free.
 */
void Free(void *);

#endif
