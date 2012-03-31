#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Alloc.h"
#include "list.h"
#include "log.h"

#include "model.h"
#include "object.h"
#include "plane.h"
#include "raytracer.h"
#include "sphere.h"

// TODO: Populate this list.
static init_shape init_type[] = {
    NULL, // light
    NULL, // spotlight
    NULL, // projector
    init_sphere,
    init_plane
};

static debug_shape debug_type[] = {
    NULL, // light
    NULL, // spotlight
    NULL, // projector
    dump_sphere,
    dump_plane
};

const int NUM_TYPES = (int) (sizeof(init_type) / sizeof(void*));

bool init_model(FILE *in, model_t *model) {
    obj_t     *new              = NULL; // The new object.
    bool      return_code       = true; // If we parsed correctly.
    char      buf[BUFFER_SIZE];         // Our input buffer.
    object_id obj_type;                 // The type of the incoming object.

    // While we can read.
    while (return_code && fgets(buf, sizeof(char) * BUFFER_SIZE, in)) {
        // Get the number code, and store if we got it.
        int matched = sscanf(buf, "%u", &obj_type);

        // Try again on the next line if we didn't find a number.
        if (matched != 1) continue;

        // Otherwise, load up the object type.
        if (obj_type >= FIRST_TYPE && (obj_type - FIRST_TYPE) < (int) NUM_TYPES) {
            if (init_type[obj_type - FIRST_TYPE] != NULL) {
                new = init_type[obj_type - FIRST_TYPE](in, obj_type);
                add_list(model->scene, new);
            } else {
                say("Valid object type %u found, but not implemented.", obj_type);
                return_code = false;
            }
        } else {
            say("Unknown object type %u found.", obj_type);
            return_code = false;
        }
    }

    return return_code;
}

void dump_model(FILE *out, model_t *model) {
    list_t *scene = model->scene;

    obj_t *obj = scene->head;

    while (obj != NULL) {
        debug_type[obj->obj_type - FIRST_TYPE](out, obj);
        obj = obj->next;
    }
}

void free_model(model_t *model) {
    Free(model->proj);
    free_list(model->lights);
    free_list(model->scene);
    Free(model);
}
