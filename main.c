#include <stdio.h>

void usage(char *);
int main(int, char **);

void usage(char *name) {
    fprintf(stderr, "Usage: %s width height\n", name);
}

int main(int argc, char* argv[]) {
    // Print usage and quit if we didn't get the right number of args.
    if (3 != argc) {
        usage(argv[0]);
        return 1;
    }
    return 0;
}
