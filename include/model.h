#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>
#include <stdio.h>

#include "list.h"
#include "object.h"
#include "projection.h"

/**
 * model_t - A model of a scene that we can raytrace. It contains a projection,
 * a list of lights, and a list of objects.
 */
typedef struct {
    proj_t *proj;
    list_t *lights;
    list_t *scene;
} model_t;

/**
 * init_shape - A function pointer type that all shape initializers must match.
 */
typedef obj_t* (*init_shape)(FILE *, object_id);

/**
 * debug_shape - A function pointer type that all shape dumbers must match.
 */
typedef void (*debug_shape)(FILE *, obj_t *);

/**
 * init_model - Initialize a model using the given input stream into the given
 * model_t. Returns if it was successful.
 *
 * @param Input stream.
 * @param Model for storing information.
 *
 * @return Success.
 */
bool init_model(FILE *, model_t *);

/**
 * dump_model - Print out the information associated with a model to the given
 * input stream.
 *
 * @param The output stream.
 * @param The model.
 */
void dump_model(FILE *, model_t *);

/**
 * free_model - Free all memory associated with the given model_t, and its
 * sub-objects.
 *
 * @param The model to free.
 */
void free_model(model_t *);

#endif
