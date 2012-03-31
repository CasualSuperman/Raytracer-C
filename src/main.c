// Library headers
#include <stdbool.h>
#include <stdio.h>

// Program headers
#include "Alloc.h"
#include "exit.h"
#include "log.h"
#include "main.h"

// Raytracer headers
#include "image.h"
#include "model.h"
#include "projection.h"
#include "list.h"

int main(int argc, char **argv) {
    // Stores the return code of various subroutines.
    bool return_code = 0;
    model_t *model  = NULL;

    // Allocate a new model.
    model = Malloc(sizeof(model_t));

    // Read in projection info and spit it back out.
    model->proj = projection_init(argc, argv, stdin);
    projection_dump(stderr, model->proj);

    // Initialize the lists for storing lights and scene objects.
    model->lights  = init_list();
    model->scene   = init_list();

    // Populate the lists and see if it was successful.
    return_code = init_model(stdin, model);

    // If it was, render the image.
    if (return_code == true) {
        dump_model(stderr, model);
        make_image(model);
        free_model(model);
    }

    // And go on our merry way.
    return EXIT_SUCCESS;
}

void usage(char *name) {
    say("Usage: %s width height", name);
}
