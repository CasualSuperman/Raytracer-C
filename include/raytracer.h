#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <stdbool.h>

enum {
	// The size of a default character buffer.
	BUFFER_SIZE = 256,
	// The number of dimensions we're rendering in.
    DIMS = 3
};

/**
 * is_zero - Returns if the given double is within a certain tolerated range of zero.
 *
 * @param The double to compare to zero.
 *
 * @return If it is considered to be close enough to zero.
 */
bool is_zero(double);

#endif
