#include <stdio.h>
#include <string.h>

#include "Alloc.h"
#include "log.h"

#include "material.h"
#include "object.h"

static int obj_id = 0;

static void get_ambient(struct object_type *obj, pixel_t *pix) {
	memcpy(pix, &(obj->material.ambient), sizeof(pixel_t));
}

static void get_diffuse(struct object_type *obj, pixel_t *pix) {
	memcpy(pix, &(obj->material.diffuse), sizeof(pixel_t));
}

static void get_specular(struct object_type *obj, pixel_t *pix) {
	memcpy(pix, &(obj->material.specular), sizeof(pixel_t));
}

obj_t* init_object(FILE *in, object_id obj_type) {
	obj_t *obj = Malloc(sizeof(obj_t));

	obj->next     = NULL;
	obj->obj_id   = obj_id++;
	obj->obj_type = obj_type;

	if (obj_type > MAX_LIGHT) {
		material_load(in, &obj->material);
	}

	obj->get_ambient  = &get_ambient;
	obj->get_diffuse  = &get_diffuse;
	obj->get_specular = &get_specular;

	return obj;
}

void dump_object(FILE *out, obj_t* obj) {
	dump_material(out, &(obj->material));
}

void free_object(obj_t *obj) {
	free(obj->priv);
	free(obj);
}
