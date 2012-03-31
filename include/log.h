#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>

/**
 * say - Prints a message and a newline to stderr. Accepts a format and any
 * number of arguments needed to fill the format specified.
 *
 * @param The format for the message being printed.
 * @param ... Any number of arguments needed to fill the format speficier.
 */
void say(char *, ...);

/**
 * fsay - Same as say, but prints its message to the given file descriptor.
 *
 * @param The format for the message being printed.
 * @param ... Any number of arguments needed to fill the format speficier.
 */
void fsay(FILE *, char *, ...);

#endif
