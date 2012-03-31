#ifndef VECTOR_H
#define VECTOR_H

/**
 * dotN - Compute the dot product of two vectors of length N.
 *
 * @param The first vector.
 * @param The second vector.
 * @param The number of dimensions of the vectors.
 *
 * @return The dot product of the two vectors.
 */
double dotN(double *, double *, int);

/**
 * lengthN - Compute the length of an N dimensional vector.
 *
 * @param The vector.
 * @param The number of dimensions it spans.
 *
 * @return The vector's length.
 */
double lengthN(double *, int);

/**
 * scaleN - Scale a vector by a scalar.
 *
 * @param The amount to scale by.
 * @param The vector to scale.
 * @param Where the result will be stored.
 * @param The number of dimensions.
 */
void scaleN(double, double *, double *, int);

/**
 * diffN - Compute the difference of two vectors.
 *
 * @param The first vector.
 * @param The second vector.
 * @param Where v2 - v1 is stored.
 * @param The number of dimensions.
 */
void diffN(double *, double *, double *, int);

/**
 * sumN - Compute the sum of two vectors.
 *
 * @param The first vector.
 * @param The second vector.
 * @param Where v1 + v2 is stored.
 * @param The number of dimensions.
 */
void sumN(double *, double *, double *, int);

/**
 * unitvecN - Scale a vector into a unit vector.
 *
 * @param The source vector.
 * @param The definiation of the scaled vector.
 * @param The numver of dimensions.
 */
void unitvecN(double *, double *, int);

/**
 * vecprnN - Print an N dimensional vector.
 *
 * @param The stream to print to.
 * @param The tag associated with the vector.
 * @param The vector.
 * @param The number of dimensions in the vector.
 */
void vecprnN(FILE *, char *, double *, int);

#endif
