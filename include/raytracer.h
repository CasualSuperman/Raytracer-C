#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <stdbool.h>

#include "image.h"
#include "model.h"
#include "projection.h"

enum {
    // The size of a default character buffer.
    BUFFER_SIZE = 256,
    // The number of dimensions we're rendering in.
    DIMS = 3
};

/**
 * is_zero - Returns if the given double is within a certain tolerated range of
 * zero.
 *
 * @param The double to compare to zero.
 *
 * @return If it is considered to be close enough to zero.
 */
bool is_zero(double);

/**
 * make_pixel - Takes a model, pixel index, and pixel and uses the model to
 * fill in the mixel.
 *
 * @param The model we're using for the image.
 * @param The row of the image we're on.
 * @param The column of the image we're on.
 * @param The pixel to store the color data in.
 */
void make_pixel(model_t *, int, int, pixel_t *);

/**
 * map_pixel_to_world - Takes a pixel position and maps it to a position in the
 * virtual world.
 *
 * @param Projection information for the scene.
 * @param The row of the pixel.
 * @param The column of the pixel.
 * @param A three dimensional vector we can store the position into.
 */
void map_pixel_to_world(proj_t *, int, int, double *);

/**
 * find_closest_obj - Finds the closest object in a scene to a given starting
 * point in a given direction.
 *
 * @param A list of objects in the scene to check.
 * @param A position to start the ray at.
 * @param A direction for the ray.
 * @param Unknown, reserved for future use.
 * @param A double to store the distance traveled to this object in.
 *
 * @return The object that was closest, or NULL.
 */
obj_t* find_closest_obj(list_t *, double [3], double [3], void *, double *);

/**
 * ray_trace - Given a model of a scene, a base and direction of a ray, and a
 * place to store the resulting color, traces a ray from a point into the
 * scene.
 *
 * @param The scene to model.
 * @param The starting location of the ray.
 * @param The direction of the ray.
 * @param Where the resulting color will be stored.
 * @param The total distance travelled.
 * @param The last object that was hit.
 */
void ray_trace(model_t *, double [3], double [3], double [3], double, obj_t *);

#endif
