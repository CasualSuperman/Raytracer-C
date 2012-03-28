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
	double T = 0;

	unitvecN(D, D, 3);

	double n_dot_d = dotN(N, D, 3);
	// If we are parallel to the plane.
	if (isZero(n_dot_d)) {
		return -1;
	}

	double n_dot_q = dotN(N, Q, 3);
	double n_dot_v = dotN(N, V, 3);

	T = (n_dot_q - n_dot_v) / n_dot_d;

	// dir * Th
	scaleN(T, D, P, 3);
	// base + (dir * Th)
	sumN(V, P, P, 3);

	if (P[2] < *(base + 2)) {
		return -1;
	}

	// Copy hit location to hitloc
	memcpy(obj->hitloc, P, sizeof(double) * 3);

	diffN(V, P, P, 3);

	return lengthN(P, 3);
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
		read = fscanf(in, "%lf %lf %lf %*s %*[\n]", &(new->normal[0]),
													&(new->normal[1]),
													&(new->normal[2]));
	} while (read == 0);

	if (read != 3) {
		say("Error loading plane normal. Read in %d values.", read);
		exit(EXIT_BAD_SCENE);
	}

	read = fscanf(in, "%lf %lf %lf", &(new->center[0]),
									 &(new->center[1]),
									 &(new->center[2]));

	if (read != 3) {
		say("Error loading plane center. Read in %d values.", read);
		exit(EXIT_BAD_SCENE);
	}

	// Preload the normal for a last hit on a plane, since it won't change.
	unitvecN(new->normal, obj->normal, 3);

	return obj;
}

void dump_plane(FILE *out, obj_t *obj) {
	plane_t *plane = (plane_t*) obj->priv;
	fsay(out, "Plane:");
	dump_object(out, obj);
	vecprnN(out, "\tCenter", plane->center, 3);
	vecprnN(out, "\tNormal", plane->normal, 3);
}
