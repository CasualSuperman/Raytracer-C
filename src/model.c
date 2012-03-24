#include <stdbool.h>
#include <stdio.h>

#include "list.h"
#include "log.h"
#include "model.h"
#include "object.h"

#include "plane.h"
#include "raytracer.h"
#include "sphere.h"

// TODO: Populate this list.
static obj_t* (*init_type[])(FILE *, object_id) = {
	NULL, // light
	NULL, // spotlight
	NULL, // projector
	sphere_init,
	plane_init
};

const int NUM_TYPES = sizeof(init_type) / sizeof(void*);

bool model_init(FILE *in, model_t *model) {
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
		if (obj_type >= FIRST_TYPE && (obj_type - FIRST_TYPE) < NUM_TYPES) {
			if (init_type[obj_type - FIRST_TYPE] != NULL) {
				new = init_type[obj_type - FIRST_TYPE](in, obj_type);
				list_add(model->scene, new);
				dump_sphere(stderr, new);
			} else {
				log("Valid object type %u found, but not implemented.", obj_type);
				return_code = false;
			}
		} else {
			log("Unknown object type %u found.", obj_type);
			return_code = false;
		}
	}

    return return_code;
}
