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
	int     row    = 0;
	int     col    = 0;
	size_t  count  = 0;

	print_header(width, height);

	for (col = 0; col < height; ++col) {
		for (row = 0; row < width; ++row) {
			make_pixel(model, row, col, pos_to_pixel(row, col, width, image));
		}
	}
	count = fwrite(image, sizeof(pixel_t), (size_t) (height * width), stdout);

	if (count < (sizeof(pixel_t) * (size_t) (width * height))) {
		say("Warning: Not all image bytes may have been written.");
	}

	Free(image);
}

static obj_t* find_closest_obj(list_t *scene, double base[3], double dir[3],
							   void *unknown, double *distance) {
	double close    = INFINITY;
	obj_t  *closest = NULL;
	obj_t  *obj     = scene->head;

	while (obj != NULL) {
		double this_dist = obj->hits(base, dir, obj);

		if (this_dist >= 0 && this_dist < close) {
			close = this_dist;
			closest = obj;
		}
		obj = obj->next;
	}

	// This is to silence the unused variable error.
	*(&unknown) = NULL;

	if (closest != NULL) {
#ifdef DEBUG_HIT
		say("Hit closest object with id %d (Distance = %lf).", closest->obj_id,
			close);
#endif
		*distance = close;
	}

	return closest;
}

static void ray_trace(model_t *model, double base[3], double dir[3],
					  double color[3], double total_dist, obj_t *last_hit) {
	obj_t *closest = find_closest_obj(model->scene, base, dir, last_hit,
									  &total_dist);

	if (closest != NULL) {
		color[0] = closest->material.ambient[0] / total_dist;
		color[1] = closest->material.ambient[1] / total_dist;
		color[2] = closest->material.ambient[2] / total_dist;
	}
}

static void make_pixel(model_t *model, int row, int col, pixel_t *pix) {
	double dir[3]   = {0, 0, 0};
	double base[3]  = {0, 0, 0};
	double color[3] = {0, 0, 0};
	int i;

	map_pixel_to_world(model->proj, row, col, base);

	diffN(model->proj->view_point, base, dir, 3);
	unitvecN(dir, dir, 3);

#ifdef DEBUG_PIXEL
	say("");

	say("Tracing pixel %d, %d. - %lf %lf (direction %lf %lf %lf)", row, col,
		base[0], base[1],
		dir[0], dir[1], dir[2]);
#endif
	ray_trace(model, model->proj->view_point, dir, color, 0.0, NULL);

	for (i = 0; i < 3; ++i) {
		if (color[i] > 1) {
			color[i] = 1;
		}
	}

	pix->r = (unsigned char) (color[0] * 255);
	pix->g = (unsigned char) (color[1] * 255);
	pix->b = (unsigned char) (color[2] * 255);
}

static void map_pixel_to_world(proj_t *proj, int row, int col, double *pos) {
	*(pos + 0) = (double) row / (proj->win_size_pixel[0] - 1)
							  *  proj->win_size_world[0]
							  - (proj->win_size_world[0] / 2.0);

	*(pos + 1) = (double) col / (-proj->win_size_pixel[1] - 1)
							  *  proj->win_size_world[1]
							  + (proj->win_size_world[1] / 2.0);

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
	return (col * height + row) + base;
}
