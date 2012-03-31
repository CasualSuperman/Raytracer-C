#ifndef MAIN_H
#define MAIN_H

/**
 * usage - Prints the proper usage of the program and exits.
 *
 * @param The name of the program.
 */
void usage(char *);

/**
 * main -  The main entry point to the program. Attempts to parse the width and
 * height passed to the program as arguments, then read in scene information
 * from stdin. Then, raytraces the scene into an image, and prints the result
 * to stdout in .ppm format, and prints debugging information to stderr.
 *
 * @param The number of arguments passed to our program.
 * @param An array of the arguments passed.
 *
 * @return The exit code of the program.
 */
int main(int, char **);

#endif
