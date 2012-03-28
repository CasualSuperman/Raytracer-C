#include <math.h>
#include <stdlib.h>

#include "Alloc.h"
#include "log.h"

#include "image.h"
#include "model.h"
#include "projection.h"
#include "vector.h"

static void print_header(int, int);
static pixel_t* pos_to_pixel(int, int, int, pixel_t *);
static void make_pixel(model_t *, int, int, pixel_t *);
static void map_pixel_to_world(proj_t *, int, int, double *);

void make_image(model_t *model) {
	proj_t  *proj  = model->proj;
	int     width  = proj->win_size_pixel[0];
	int     height = proj->win_size_pixel[1];
	pixel_t *image = Calloc((size_t) (width * height), sizeof(pixel_t));

	print_header(width, height);

	for (int row = 0; row < width; ++row) {
		for (int col = 0; col < height; ++col) {
			make_pixel(model, row, col, pos_to_pixel(row, col, height, image));
		}
	}
	fwrite(image, sizeof(pixel_t), (size_t) (height * width), stdout);
}

static void make_pixel(model_t *model, int row, int col, pixel_t *pix) {
	double base[3] = {0, 0, 0};
	double dir[3]  = {0, 0, 0};
	double close   = INFINITY;

	map_pixel_to_world(model->proj, row, col, base);

	diffN(base, model->proj->view_point, dir, 3);
	unitvecN(dir, dir, 3);

	obj_t *obj     = model->scene->head;
	obj_t *closest = NULL;

	while (obj != NULL) {
		double distance = obj->hits(base, dir, obj);
		if (distance > 0 && distance < close) {
			close = distance;
			closest = obj;
		}
		obj = obj->next;
	}

	if (closest != NULL) {
		closest->get_ambient(closest, pix);
	}
}

static void map_pixel_to_world(proj_t *proj, int row, int col, double *pos) {
	*(pos + 0) = (double) row / (proj->win_size_pixel[0] - 1)
							  *  proj->win_size_world[0]
							  - (proj->win_size_world[0] / 2.0);

	*(pos + 1) = (double) col / (proj->win_size_pixel[1] - 1)
							  *  proj->win_size_world[1]
							  - (proj->win_size_world[1] / 2.0);

	*(pos + 2) = 0;
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
