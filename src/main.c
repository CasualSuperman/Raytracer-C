// Library headers
#include <stdio.h>

// Program headers
#include "Alloc.h"
#include "exit.h"
#include "main.h"

// Raytracer headers
#include "image.h"
#include "model.h"
#include "projection.h"
#include "list.h"

int main(int argc, char **argv) {
    // Stores the return code of various subroutines.
    int return_code = 0;
    model_t *model  = NULL;

    // Allocate a new model.
    model = Malloc(sizeof(model_t));

    // Read in projection info and spit it back out.
    model->proj = projection_init(argc, argv, stdin);
    projection_dump(stderr, model->proj);

    // Initialize the lists for storing lights and scene objects.
    model->lights  = list_init();
    model->scene   = list_init();

    // Populate the lists and see if it was successful.
    return_code = model_init(stdin, model);

    // If it was, render the image.
    if (return_code == 0) {
        make_image(model);
    }

    // And go on our merry way.
    return EXIT_SUCCESS;
}

void usage(char *name) {
    fprintf(stderr, "Usage: %s width height\n", name);
}
