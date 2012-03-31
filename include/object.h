#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>

#include "material.h"

// Doing this slightly differently for type-safety.
typedef enum {
    FIRST_TYPE = 10,
    MAX_LIGHT  = 11,

    LIGHT      = 10,
    SPOTLIGHT  = 11,
    PROJECTOR  = 12,
    SPHERE     = 13,
    PLANE      = 14
} object_id;

typedef struct object_type {
    struct object_type *next;
    int                obj_id;
    object_id          obj_type;

    double (*hits)(double *, double *, struct object_type *);

    void (*get_ambient )(struct object_type *, double *);
    void (*get_diffuse )(struct object_type *, double *);
    void (*get_specular)(struct object_type *, double *);

    material_t material;

    void (*get_emissivity)(struct object_type *, double *);
    double emissivity[3];
    void *priv;

    double hitloc[3];
    double normal[3];
} obj_t;

/**
 * init_object - Allocate an object, read in information about it from the
 * given file descriptor, and return the initialized object.
 *
 * @param The file descriptor to read from.
 * @param The type id of the object being read in.
 *
 * @return An initialized object.
 */
obj_t* init_object(FILE *, object_id);

/**
 * dump_object - Print information about the given object to the given output
 * stream.
 *
 * @param Output stream.
 * @param The object to dump.
 */
void dump_object(FILE *, obj_t *);

/**
 * free_object - Free the given object and all its sub-data.
 *
 * @param The object to free.
 */
void free_object(obj_t *);

#endif
