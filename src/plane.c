#include <stdio.h>
#include <string.h>

#include "Alloc.h"
#include "exit.h"
#include "log.h"

#include "object.h"
#include "plane.h"
#include "vector.h"

static double hits_plane(double *base, double *dir, struct object_type *obj) {
	double temp[3] = {0, 0, 0};
	plane_t *plane = (plane_t*) obj->priv;

	double n_dot_temp = -1;

	double n_dot_d = dotN(plane->normal, dir, 3);
	// If we are parallel to the plane.
	if (isZero(n_dot_d)) {
		return -1;
	}

	diffN(plane->center, base, temp, 3);
	n_dot_temp = dotN(temp, plane->normal, 3);

	if (n_dot_temp <= 0) {
		return -1;
	}

	// dir * Th
	scaleN(n_dot_temp, dir, temp, 3);
	// base + (dir * Th)
	sumN(temp, base, temp, 3);

	// Copy hit location to hitloc
	memcpy(obj->hitloc, temp, sizeof(double) * 3);

	return n_dot_temp;
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
		say("Error loading plane center. Read in %d values.", read);
		exit(EXIT_BAD_SCENE);
	}

		read = fscanf(in, "%lf %lf %lf", &(new->normal[0]),
										 &(new->normal[1]),
										 &(new->normal[2]));

	if (read != 3) {
		say("Error loading plane normal. Read in %d values.", read);
		exit(EXIT_BAD_SCENE);
	}

	// Preload the normal for a last hit on a plane, since it won't change.
	unitvecN(new->normal, obj->normal, 3);

	return obj;
}

// TODO: Write this.
void dump_plane(FILE *out, obj_t *obj) {
	plane_t *plane = (plane_t*) obj->priv;
	fsay(out, "Plane:");
	dump_object(out, obj);
	vecprnN(out, "\tCenter", plane->center, 3);
	vecprnN(out, "\tNormal", plane->normal, 3);
}
