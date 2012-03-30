#ifndef PLANE_H
#define PLANE_H

#include "object.h"

typedef struct {
	double center[3];
	double normal[3];
} plane_t;

/**
 * init_plane - Read information from the given file descriptor about an object
 * with the provided type id.
 *
 * @param The file descriptor to read from.
 * @param The object type id.
 *
 * @return An initialized object.
 */
obj_t* init_plane(FILE *, object_id);

/**
 * dump_plane - Print information about the provided plane to the given file
 * descriptor.
 *
 * @param The file descriptor to print to.
 * @param The object to print information about.
 */
void dump_plane(FILE *, obj_t *);

#endif
