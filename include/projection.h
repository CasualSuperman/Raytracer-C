#ifndef PROJECTION_H
#define PROJECTION_H

#include <stdio.h>

typedef struct {
    int dummy;
} proj_t;

proj_t* projection_init(int, char**, FILE*);

void projection_dump(FILE *, proj_t*);

#endif
