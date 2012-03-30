#ifndef EXIT_H
#define EXIT_H

/*
 * These are the various exit codes used by the program.
 * EXIT_SUCCESS is already defined, it is simply included in a comment here for
 * completeness.
 */
enum {
//  EXIT_SUCCESS = 0,
    EXIT_FAILED_ALLOC = 1,
	EXIT_BAD_PARAMS   = 2,
	EXIT_BAD_SCENE    = 3
};

#endif
