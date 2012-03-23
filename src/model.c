#include <stdbool.h>
#include <stdio.h>

#include "list.h"
#include "model.h"
#include "object.h"

#include "plane.h"
#include "raytracer.h"
#include "sphere.h"

// TODO: Populate this list.
static obj_t* (*init_type[])(FILE *, object_id) = {
	plane_init,
	sphere_init
};

#define NUM_TYPES sizeof(init_type) / sizeof(void*)

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
		if (!matched) continue;

		// Otherwise, load up the object type.
		if (obj_type >= FIRST_TYPE && obj_type < NUM_TYPES) {
			new = init_type[obj_type](in, obj_type);
			if (new) {
				list_add(model->scene, new);
			} else {
				fprintf(stderr,
					    "Valid object type %u found, but not implemented.\n",
					    obj_type);
				return_code = false;
			}
		} else {
			fprintf(stderr, "Unknown object type %u found.\n", obj_type);
			return_code = false;
		}
	}

    return return_code;
}
