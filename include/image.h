#ifndef IMAGE_H
#define IMAGE_H

#include "model.h"

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} pixel_t;

void make_image(model_t *);
static pixel_t* pos_to_pixel(int, int, int, pixel_t *);

#endif
