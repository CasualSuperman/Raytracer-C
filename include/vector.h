#ifndef VECTOR_H
#define VECTOR_H

/**
 * Returns the dot product of v1 and v2, vectors of dimensionality size.
 */
double dotN(double* v1, double* v2, int size);

/**
 * Scales the input vector, vin, by the scale and puts it into vout
 */
void scaleN(double scale, double* vin, double* vout, int size);

/**
 * Returns the length of the vector vin.
 */
double lengthN(double* vin, int size);

/**
 * Puts v2 - v1 into vout.
 */
void diffN(double* v1, double* v2, double* vout, int size);

/**
 * Puts v1 + v2 into vout.
 */
void sumN(double* v1, double* v2, double* vout, int size);

/**
 * Puts vin / ||vin|| into vout.
 */
void unitvecN(double* vin, double* vout, int size);

/**
 * Prints vin with the label label.
 */
void vecprnN(char* label, double* vin, int size);
#endif
