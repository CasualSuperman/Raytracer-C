#ifndef PROJECTION_H
#define PROJECTION_H

#include <stdio.h>

typedef struct {
    int    win_size_pixel[2];
	double win_size_world[2];
	double view_point[3];
} proj_t;

proj_t* projection_init(int, char **, FILE *);

void projection_dump(FILE *, proj_t*);

#endif
