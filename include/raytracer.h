#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <stdbool.h>

enum {
	// The size of a default character buffer.
	BUFFER_SIZE = 256,
	// The number of dimensions we're rendering in.
    DIMS = 3
};

bool isZero(double);

#endif
