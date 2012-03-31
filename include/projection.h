#ifndef PROJECTION_H
#define PROJECTION_H

#include <stdio.h>

typedef struct {
    int    win_size_pixel[2];
	double win_size_world[2];
	double view_point[3];
} proj_t;

/**
 * projection_init - Allocates a new proj_t, fills it in using the provided
 * input stream, and returns the result. Exits on failure.
 *
 * @param The number of arguments passed to main.
 * @param The arguments passed to main.
 * @param The input stream with information about the proj_t.
 *
 * @return The filled in proj_t.
 */
proj_t* projection_init(int, char **, FILE *);

/**
 * projection_dump - Print information about the projection to the given file
 * descriptor.
 *
 * @param The output stream.
 * @param The proj_t to dump.
 */
void projection_dump(FILE *, proj_t*);

#endif
