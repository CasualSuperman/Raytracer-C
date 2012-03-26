#ifndef PLANE_H
#define PLANE_H

#include "object.h"

typedef struct {
	double center[3];
	double normal[3];
} plane_t;

obj_t* init_plane(FILE *, object_id);
void dump_plane(FILE *, obj_t *);

#endif
