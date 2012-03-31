#include <math.h>
#include <stdbool.h>

#include "image.h"
#include "model.h"
#include "projection.h"
#include "raytracer.h"

static const double TOLERANCE = 0.0000000001;

inline bool is_zero(double comp) {
	return fabs(comp) <= TOLERANCE;
}

void map_pixel_to_world(proj_t *proj, int row, int col, double *pos) {
	*(pos + 0) = (double) row / (proj->win_size_pixel[0] - 1)
							  *  proj->win_size_world[0]
							  - (proj->win_size_world[0] / 2.0);

	*(pos + 1) = (double) col / (-proj->win_size_pixel[1] - 1)
							  *  proj->win_size_world[1]
							  + (proj->win_size_world[1] / 2.0);

	*(pos + 2) = 0;
}

void ray_trace(model_t *model, double base[3], double dir[3],
					  double color[3], double total_dist, obj_t *last_hit) {
	obj_t *closest = find_closest_obj(model->scene, base, dir, last_hit,
									  &total_dist);

	if (closest != NULL) {
		color[0] = closest->material.ambient[0] / total_dist;
		color[1] = closest->material.ambient[1] / total_dist;
		color[2] = closest->material.ambient[2] / total_dist;
	} else {
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
	}
}

obj_t* find_closest_obj(list_t *scene, double base[3], double dir[3],
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
