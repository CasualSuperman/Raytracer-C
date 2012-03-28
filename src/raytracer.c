#include <math.h>
#include <stdbool.h>

#include "raytracer.h"

static const double TOLERANCE = 0.00000001;

bool isZero(double comp) {
	return fabs(comp) <= TOLERANCE;
}
