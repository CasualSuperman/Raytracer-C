#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>
#include <stdio.h>

#include "list.h"
#include "object.h"
#include "projection.h"

typedef struct {
    proj_t *proj;
    list_t *lights;
    list_t *scene;
} model_t;

typedef obj_t* (*init_shape)(FILE *, object_id);
typedef void (*debug_shape)(FILE *, obj_t *);

bool init_model(FILE *, model_t *);
void dump_model(FILE *, model_t *);
void free_model(model_t *);

#endif
