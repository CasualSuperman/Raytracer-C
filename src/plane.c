#include <stdio.h>

#include "Alloc.h"
#include "exit.h"
#include "log.h"

#include "object.h"
#include "plane.h"
#include "vector.h"

static double hits_plane(double *base, double *dir, struct object_type *obj) {
	base = NULL;
	dir = NULL;
	obj = NULL;
//	sphere_t *sphere = (sphere_t *) obj->priv;
	return 0;
}

obj_t* init_plane(FILE *in, object_id id) {
	// Initialize our objects and variables.
	obj_t   *obj = init_object(in, id);
	plane_t *new = Malloc(sizeof(plane_t));
	int     read = 0;

	// Store our data in the object.
	obj->priv = new;
	obj->hits = &hits_plane;

	// Load in the information specific to a sphere.
	// While we're reading empty lines/comments.
	do {
		read = fscanf(in, "%lf %lf %lf %*s %*[\n]", &(new->center[0]),
													&(new->center[1]),
													&(new->center[2]));
	} while (read == 0);

	if (read != 3) {
		log("Error loading sphere center. Read in %d values.", read);
		exit(EXIT_BAD_SCENE);
	}

		read = fscanf(in, "%lf %lf %lf", &(new->normal[0]),
										 &(new->normal[1]),
										 &(new->normal[2]));

	if (read != 3) {
		log("Error loading sphere radius. Read in %i values.", read);
		exit(EXIT_BAD_SCENE);
	}

	return obj;
}

// TODO: Write this.
void dump_plane(FILE *out, obj_t *obj) {
	plane_t *plane = (plane_t*) obj->priv;
	flog(out, "Plane:");
	dump_object(out, obj);
	vecprnN(out, "\tCenter", plane->center, 3);
	vecprnN(out, "\tNormal", plane->normal, 3);
}
