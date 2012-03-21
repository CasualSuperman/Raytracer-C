// Library headers
#include <stdio.h>

// Program headers
#include "Alloc.h"
#include "exit.h"
#include "main.h"

// Raytracer headers
#include "model.h"

int main(int argc, char* argv[]) {
    // Print usage and quit if we didn't get the right number of args.
    if (3 != argc) {
        usage(argv[0]);
        return 1;
    }
    
    model_t *model  = Malloc(sizeof(model_t));
    model->proj = projection_init(argc, argv, stdin);
/*
    int     rc;
    model->proj = projection_init(argc, argv, stdin);
    projection_dump(stderr, model->proj);
    model->lights  = list_init();
    model->scene   = list_init();
    rc = model_init(stdin, model);
    model_dump(stderr, model);
    if (rc == 0)
        make_image(model);
*/
    return EXIT_SUCCESS;
}

void usage(char *name) {
    fprintf(stderr, "Usage: %s width height\n", name);
}
