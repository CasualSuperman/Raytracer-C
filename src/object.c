#include <stdio.h>

#include "Alloc.h"

#include "material.h"
#include "object.h"

static int obj_id = 0;

obj_t* object_init(FILE *in, object_id obj_type) {
	obj_t *obj = Malloc(sizeof(obj_t));

	obj->next     = NULL;
	obj->obj_id   = obj_id++;
	obj->obj_type = obj_type;

	if (obj_type > MAX_LIGHT) {
		material_load(in, &obj->material);
	}

	return obj;
}