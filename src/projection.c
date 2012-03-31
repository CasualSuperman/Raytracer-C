#include <stdio.h>

#include "Alloc.h"
#include "exit.h"
#include "log.h"
#include "main.h"

#include "projection.h"
#include "raytracer.h"

proj_t* projection_init(int argc, char **argv, FILE *in) {
    char line[BUFFER_SIZE] = {0};
    char *width = NULL;
    char *height = NULL;
    proj_t *proj = NULL;
    int count = 0;

    if (argc != 3) {
        usage(*argv);
        exit(EXIT_BAD_PARAMS);
    }

    width  = *(argv + 1);
    height = *(argv + 2);
    proj   = Malloc(sizeof(proj_t));

    proj->win_size_pixel[0] = atoi(width);
    proj->win_size_pixel[1] = atoi(height);

    // Read next line and check for error at the same time.
    if (fgets(line, BUFFER_SIZE, in) == NULL) {
        say("Unexpected EOF found while reading projection information.");
        exit(EXIT_BAD_PARAMS);
    }

    count = sscanf(line, "%lf %lf",
                         &(proj->win_size_world[0]),
                         &(proj->win_size_world[1]));
    if (count != 2) {
        say("Only %d world size paramters found.", count);
        exit(EXIT_BAD_PARAMS);
    }

    // Read next line and check for error at the same time.
    if (fgets(line, BUFFER_SIZE, in) == NULL) {
        say("Unexpected EOF found while reading projection information.");
        exit(EXIT_BAD_PARAMS);
    }

    count = sscanf(line, "%lf %lf %lf",
                         &(proj->view_point[0]),
                         &(proj->view_point[1]),
                         &(proj->view_point[2]));
    if (count != 3) {
        say("Only %d view point paramters found.", count);
        exit(EXIT_BAD_PARAMS);
    }

    return proj;
}

void projection_dump(FILE *out, proj_t *proj) {
    fsay(out, "Projection:");
    fsay(out, "\tSCREEN");
    fsay(out, "\t\twidth: %d", proj->win_size_pixel[0]);
    fsay(out, "\t\theight: %d", proj->win_size_pixel[1]);
    fsay(out, "\tWORLD");
    fsay(out, "\t\twidth: %lf", proj->win_size_world[0]);
    fsay(out, "\t\theight: %lf", proj->win_size_world[1]);
    fsay(out, "\tVIEWPT");
    fsay(out, "\t\tx: %lf", proj->view_point[0]);
    fsay(out, "\t\ty: %lf", proj->view_point[1]);
    fsay(out, "\t\tz: %lf", proj->view_point[2]);
}
