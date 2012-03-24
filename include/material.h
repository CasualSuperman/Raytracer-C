#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdbool.h>

typedef struct {
	double ambient[3];
	double diffuse[3];
	double specular[3];
} material_t;

bool material_load(FILE *, material_t *);
void dump_material(FILE *, material_t *);

#endif
