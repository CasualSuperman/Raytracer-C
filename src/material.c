#include <stdbool.h>
#include <stdio.h>

#include "material.h"
#include "raytracer.h"

bool material_load(FILE *in, material_t *mat) {
	char  buf[BUFFER_SIZE];
	char *finished;
	int   matched;

	// Load in a new line. Try to read in 3 doubles. If we fail, return false.
	finished = fgets(buf, sizeof(char) * BUFFER_SIZE, in);

	if (!finished) {
		return false;
	}

	matched = sscanf(buf, "%lf %lf %lf", &(mat->ambient[0]),
										 &(mat->ambient[1]),
										 &(mat->ambient[2]));
	if (matched != 3) {
		return false;
	}

	// Load in a new line. Try to read in 3 doubles. If we fail, return false.
	finished = fgets(buf, sizeof(char) * BUFFER_SIZE, in);

	if (!finished) {
		return false;
	}

	matched = sscanf(buf, "%lf %lf %lf", &(mat->diffuse[0]),
										 &(mat->diffuse[1]),
										 &(mat->diffuse[2]));
	if (matched != 3) {
		return false;
	}

	// Load in a new line. Try to read in 3 doubles. If we fail, return false.
	finished = fgets(buf, sizeof(char) * BUFFER_SIZE, in);

	if (!finished) {
		return false;
	}

	matched = sscanf(buf, "%lf %lf %lf", &(mat->specular[0]),
										 &(mat->specular[1]),
										 &(mat->specular[2]));
	if (matched != 3) {
		return false;
	}
	return true;
}
