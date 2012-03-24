#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>

#include "material.h"
#include "raytracer.h"

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

    double hitloc[DIMS];
    double normal[DIMS];
} obj_t;

obj_t* object_init(FILE *, object_id);
void dump_object(FILE *, obj_t *);

#endif
