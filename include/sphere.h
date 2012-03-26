#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

typedef struct {
	double center[3];
	double radius;
} sphere_t;

obj_t* init_sphere(FILE *, object_id);
void dump_sphere(FILE *, obj_t *);

#endif
