#include <math.h>
#include <stdio.h>

#include "vector.h"

/**
 * Compute the dot product of two vectors.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param size The dimensionality of the vectors.
 *
 * @return The dot product.
 */
inline double dotN(double* v1, double* v2, int size) {
    double result = 0;
    int i;
    for (i = 0; i < size; ++i, ++v1, ++v2) {
        result += *v1 * *v2;
    }
    return result;
}

/**
 * Scale a vector by a constant.
 *
 * @param scale The constant.
 * @param vim The input vector.
 * @param vout The output vector.
 * @param size The dimensionality of the vectors.
 */
inline void scaleN(double scale, double* vin, double* vout, int size) {
    int i;
    for (i = 0; i < size; ++i, ++vin, ++vout) {
        *vout = *vin * scale;
    }
}

/**
 * Compute the length of a vector.
 *
 * @param vim The input vector.
 * @param size The dimensionality of the vector.
 *
 * @return The length
 */
inline double lengthN(double* vin, int size) {
    return sqrt(dotN(vin, vin, size));
}

/**
 * Compute the difference of two vectors.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param vout Where v2 - v1 is stored.
 * @param size The dimensionality of the vectors.
 */
inline void diffN(double* v1, double* v2, double* vout, int size) {
    int i;
    for (i = 0; i < size; ++i, ++v1, ++v2, ++vout) {
        *vout = *v2 - *v1;
    }
}

/**
 * Compute the sum of two vectors.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param vout Where v1 + v2 is stored.
 * @param size The dimensionality of the vectors.
 */
inline void sumN(double* v1, double* v2, double* vout, int size) {
    int i;
    for (i = 0; i < size; ++i, ++v1, ++v2, ++vout) {
        *vout = *v2 + *v1;
    }
}

/**
 * Convert a vector into a unit vector.
 *
 * @param vin The input vector.
 * @param vout The output vector.
 * @param size The dimensionality of th vectors.
 */
inline void unitvecN(double* vin, double* vout, int size) {
    double mag = 1 / lengthN(vin, size);
    int i;
    for (i = 0; i < size; ++i, ++vin, ++vout) {
        *vout = *vin * mag;
    }
}

/**
 * Print out a vector.
 *
 * @param label The vector's label.
 * @param vin The vector to print.
 * @param size The dimensionality of the vector.
 */
void vecprnN(FILE *out, char* label, double* vin, int size) {
    fprintf(out, "%s: <", label);
    if (size-- > 0) {
        fprintf(out, "%.3lf", *vin++);
        while (size--) {
            fprintf(out, ", %.3lf", *vin++);
        }
    }
    fprintf(out, ">\n");
}
