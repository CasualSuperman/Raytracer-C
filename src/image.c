#include <stdlib.h>

#include "Alloc.h"
#include "log.h"

#include "image.h"
#include "model.h"
#include "projection.h"

void make_image(model_t *model) {
	proj_t  *proj  = model->proj;
	int     width  = proj->win_size_pixel[0];
	int     height = proj->win_size_pixel[1];
	pixel_t *image = Malloc((size_t) (width * height) * sizeof(pixel_t));

	for (int row = 0; row < width; ++row) {
		for (int col = 0; col < height; ++col) {
			*(pos_to_pixel(row, col, height, image)) = (pixel_t) {255, 0, 0};
		}
	}
}

static inline pixel_t* pos_to_pixel(int row, int col, int height, pixel_t *base) {
	return (row * height + col) + base;
}
