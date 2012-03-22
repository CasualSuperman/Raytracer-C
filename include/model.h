#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>
#include <stdio.h>

#include "list.h"
#include "projection.h"

typedef struct {
    proj_t *proj;
    list_t *lights;
    list_t *scene;
} model_t;

bool model_init(FILE *, model_t *);

#endif
