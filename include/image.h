#ifndef IMAGE_H
#define IMAGE_H

#include "model.h"

/**
 * A pixel is made up of R, G, and B.
 */
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} pixel_t;

/**
 * make_image -  Takes an initialized model object and renders the scene,
 * printing the output to stdout in .ppm format.
 *
 * @param The model we want to make an image out of.
 */
void make_image(model_t *);

#endif
