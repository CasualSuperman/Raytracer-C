#include <math.h>
#include <stdio.h>

#include "Alloc.h"
#include "exit.h"
#include "log.h"

#include "object.h"
#include "sphere.h"
#include "vector.h"

// TODO: Write this.
static double hits_sphere(double *base, double *dir, struct object_type *obj) {
	sphere_t *sphere = (sphere_t *) obj->priv;
	double *D   = dir;
	double V[3] = {0, 0, 0};
	double r    = sphere->radius;
	double a    = 0;
	double b    = 0;
	double c    = 0;
	double discriminant = 0;
	double T = 0;

	diffN(sphere->center, base, V, 3);

	a = dotN(D, D, 3);
	b = 2 * dotN(V, D, 3);
	c = dotN(V, V, 3) - r * r;

#ifdef DEBUG_SPHERE
	say("a: %lf, b: %lf, c: %lf", a, b, c);
#endif

	discriminant = (b * b - 4 * a * c);

#ifdef DEBUG_SPHERE
	say("Sphere discriminant is %lf (T = %lf).", discriminant, T);
#endif

	if (discriminant <= 0) {
		return -1;
	}

	T = (-b - sqrt(discriminant)) / (2 * a);

	return T;
}

obj_t* init_sphere(FILE *in, object_id id) {
	// Initialize our objects and variables.
	char     *buf = Calloc((size_t) BUFFER_SIZE, sizeof(char));
	obj_t    *obj = init_object(in, id);
	sphere_t *new = Malloc(sizeof(sphere_t));
	int      read = 0;

	// Store our data in the object.
	obj->priv = new;
	obj->hits = &hits_sphere;

	// Load in the information specific to a sphere.
	// While we're reading empty lines/comments.
	do {
		if (buf != fgets(buf, BUFFER_SIZE, in)) {
			Free(buf);
			say("Unexpected end of file while reading sphere center.");
			exit(EXIT_BAD_SCENE);
		}
		
		read = sscanf(buf, "%lf %lf %lf", &(new->center[0]),
										  &(new->center[1]),
										  &(new->center[2]));
	} while (read == -1);

	if (read != 3) {
		say("Error loading sphere center. Read in %d values.", read);
		Free(buf);
		exit(EXIT_BAD_SCENE);
	}

	if (buf != fgets(buf, BUFFER_SIZE, in)) {
		Free(buf);
		say("Unexpected end of file while reading sphere radius.");
		exit(EXIT_BAD_SCENE);
	}
		
	read = sscanf(buf, "%lf", &(new->radius));
	Free(buf);

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
