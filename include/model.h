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

bool model_init(FILE *, model_t *);

#endif
