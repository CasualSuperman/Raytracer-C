#include <stdio.h>

#include "Alloc.h"
#include "exit.h"
#include "log.h"

#include "object.h"
#include "sphere.h"
#include "vector.h"

// TODO: Write this.
static double hits_sphere(double *base, double *dir, struct object_type *obj) {
	base = NULL;
	dir = NULL;
	obj = NULL;
//	sphere_t *sphere = (sphere_t *) obj->priv;
	return -1;
}

obj_t* init_sphere(FILE *in, object_id id) {
	// Initialize our objects and variables.
	obj_t    *obj = init_object(in, id);
	sphere_t *new = Malloc(sizeof(sphere_t));
	int      read = 0;

	// Store our data in the object.
	obj->priv = new;
	obj->hits = &hits_sphere;

	// Load in the information specific to a sphere.
	// While we're reading empty lines/comments.
	do {
		read = fscanf(in, "%lf %lf %lf %*s %*[\n]", &(new->center[0]),
													&(new->center[1]),
													&(new->center[2]));
	} while (read == 0);

	if (read != 3) {
		say("Error loading sphere center. Read in %d values.", read);
		exit(EXIT_BAD_SCENE);
	}

	read = fscanf(in, "%lf", &(new->radius));

	if (read != 1) {
		say("Error loading sphere radius. Read in %d values.", read);
		exit(EXIT_BAD_SCENE);
	}

	return obj;
}

void dump_sphere(FILE *out, obj_t *obj) {
	sphere_t *sphere = (sphere_t*) obj->priv;
	fsay(out, "Sphere:");
	dump_object(out, obj);
	vecprnN(out, "\tCenter", sphere->center, 3);
	fsay(out, "\tRadius: %lf", sphere->radius);
}
