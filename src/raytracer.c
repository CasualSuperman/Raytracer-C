#include <math.h>
#include <stdbool.h>

#include "raytracer.h"

static const double TOLERANCE = 0.0000000001;

inline bool isZero(double comp) {
	return fabs(comp) <= TOLERANCE;
}
