#include <stdlib.h>

#include "Alloc.h"
#include "log.h"

#include "image.h"
#include "model.h"
#include "projection.h"

static void print_header(int, int);
static pixel_t* pos_to_pixel(int, int, int, pixel_t *);

void make_image(model_t *model) {
	proj_t  *proj  = model->proj;
	int     width  = proj->win_size_pixel[0];
	int     height = proj->win_size_pixel[1];
	pixel_t *image = Calloc((size_t) (width * height), sizeof(pixel_t));

	print_header(width, height);

	for (int row = 0; row < width; ++row) {
		for (int col = 0; col < height; ++col) {
			*(pos_to_pixel(row, col, height, image)) = (pixel_t) {0, 0, 0};
		}
	}
	fwrite(image, sizeof(pixel_t), (size_t) (height * width), stdout);
}

static void print_header(int width, int height) {
	printf("P6");
	printf("\n");
	printf("%d %d", width, height);
	printf("\n");
	printf("255");
	printf("\n");
	fflush(stdout);
}

static inline pixel_t* pos_to_pixel(int row, int col, int height, pixel_t *base) {
	return (row * height + col) + base;
}
