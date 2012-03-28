#include <math.h>
#include <stdbool.h>

#include "raytracer.h"

static const double variance = 0x10;

inline bool isZero(double comp) {
	return (fabs(comp) <= variance);
}
