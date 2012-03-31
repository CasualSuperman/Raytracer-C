#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

typedef struct {
    double center[3];
    double radius;
} sphere_t;

/**
 * init_sphere - Read information from the given file descriptor about an object
 * with the provided type id.
 *
 * @param The file descriptor to read from.
 * @param The object type id.
 *
 * @return An initialized object.
 */
obj_t* init_sphere(FILE *, object_id);

/**
 * dump_sphere - Print information about the provided sphere to the given file
 * descriptor.
 *
 * @param The file descriptor to print to.
 * @param The object to print information about.
 */
void dump_sphere(FILE *, obj_t *);

#endif
