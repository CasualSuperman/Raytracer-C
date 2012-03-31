#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdbool.h>

/**
 * material_t - Storage for information about the material of a shape.
 */
typedef struct {
    double ambient[3];
    double diffuse[3];
    double specular[3];
} material_t;

/**
 * material_load - Read in material information from the given file descriptor.
 * Returns whether or not the parsing was successful.
 *
 * @param The file descriptor to read from.
 * @param The allocated material to write to.
 *
 * @return If the parsing was successful.
 */
bool material_load(FILE *, material_t *);

/**
 * dump_material - Prints the material information to the given file descriptor
 * about the given material.
 *
 * @param The file descriptor to write to.
 * @param The material information to dump.
 */
void dump_material(FILE *, material_t *);

#endif
