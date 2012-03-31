#include <stdio.h>
#include <string.h>

#include "Alloc.h"
#include "exit.h"
#include "log.h"

#include "object.h"
#include "plane.h"
#include "vector.h"

// Th = (N dot Q  - N dot V) / (N dot D)
static double hits_plane(double *base, double *dir, struct object_type *obj) {
	plane_t *plane = (plane_t*) obj->priv;
	double *Q = plane->center;
	double *N = plane->normal;
	double *D = dir;
	double *V = base;
	double P[3] = {0, 0, 0};
	double n_dot_d = dotN(N, D, 3);
	double T = 0;

	// If we are parallel to the plane.
	if (is_zero(n_dot_d)) {
#ifdef DEBUG_PLANE
		say("Plane is parallel.");
#endif
		return -1;
	}

	T = (dotN(N, Q, 3) - dotN(N, V, 3)) / n_dot_d;

	// dir * Th
	scaleN(T, D, P, 3);
	// base + (dir * Th)
	sumN(V, P, P, 3);

	if (P[2] > 0 && !is_zero(P[2])) {
#ifdef DEBUG_PLANE
		say("Plane is behind viewer. (T = %lf)", T);
#endif
		return -1;
	}

	// Copy hit location to hitloc
	memcpy(obj->hitloc, P, sizeof(double) * 3);

#ifdef DEBUG_PLANE
	say("Hit plane %d at point %lf %lf %lf (T = %lf)", obj->obj_id, P[0], P[1], P[2], T);
#endif

	return T;
}

obj_t* init_plane(FILE *in, object_id id) {
	// Initialize our objects and variables.
	char    *buf = Malloc((size_t) BUFFER_SIZE * sizeof(char));
	obj_t   *obj = init_object(in, id);
	plane_t *new = Malloc(sizeof(plane_t));
	int     read = 0;

	// Store our data in the object.
	obj->priv = new;
	obj->hits = &hits_plane;

	// Load in the information specific to a sphere.
	// While we're reading empty lines/comments.
	do {
		if (buf != fgets(buf, BUFFER_SIZE, in)) {
			Free(buf);
			say("Unexpected end of file while reading plane normal.");
			exit(EXIT_BAD_SCENE);
		}
		read = sscanf(buf, "%lf %lf %lf %*s %*[\n]", &(new->normal[0]),
													 &(new->normal[1]),
													 &(new->normal[2]));
	} while (read == -1);

	if (read != 3) {
		say("Error loading plane normal. Read in %d values.", read);
		exit(EXIT_BAD_SCENE);
	}

	if (buf != fgets(buf, BUFFER_SIZE, in)) {
		Free(buf);
		say("Unexpected end of file while reading plane center.");
		exit(EXIT_BAD_SCENE);
	}

	read = sscanf(buf, "%lf %lf %lf", &(new->center[0]),
									  &(new->center[1]),
									  &(new->center[2]));

	if (read != 3) {
		say("Error loading plane center. Read in %d values.", read);
		exit(EXIT_BAD_SCENE);
	}

	// Preload the normal for a last hit on a plane, since it won't change.
	unitvecN(new->normal, obj->normal, 3);

	Free(buf);

	return obj;
}

void dump_plane(FILE *out, obj_t *obj) {
	plane_t *plane = (plane_t*) obj->priv;
	fsay(out, "Plane:");
	dump_object(out, obj);
	vecprnN(out, "\tCenter", plane->center, 3);
	vecprnN(out, "\tNormal", plane->normal, 3);
}
