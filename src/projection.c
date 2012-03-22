#include <stdio.h>

#include "Alloc.h"
#include "exit.h"
#include "main.h"

#include "projection.h"
#include "raytracer.h"

proj_t* projection_init(int argc, char **argv, FILE *in) {
	char *width, *height;
	proj_t *proj;
	int count;

	if (argc != 3) {
		usage(*argv);
		exit(EXIT_BAD_PARAMS);
	}

	width  = *(argv + 1);
	height = *(argv + 2);
	proj   = Malloc(sizeof(proj_t));

	proj->win_size_pixel[0] = atoi(width);
	proj->win_size_pixel[1] = atoi(height);

	count = fscanf(in, "%lf %lf",
						&(proj->win_size_world[0]),
						&(proj->win_size_world[1]));
	if (count != 2) {
		exit(EXIT_BAD_PARAMS);
	}
	
	count = fscanf(in, "%lf %lf %lf",
						&(proj->view_point[0]),
						&(proj->view_point[1]),
						&(proj->view_point[2]));
	if (count != 3) {
		exit(EXIT_BAD_PARAMS);
	}

	return proj;
}

void projection_dump(FILE *out, proj_t *proj) {
	fprintf(out, "Projection:\n");
	fprintf(out, "\tSCREEN\twidth: %d\n\t\theight: %d\n",
			proj->win_size_pixel[0], proj->win_size_pixel[1]);
	fprintf(out, "\tWORLD\twidth: %lf\n\t\theight: %lf\n",
			proj->win_size_world[0], proj->win_size_world[1]);
	fprintf(out, "\tVIEWPT\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n",
			proj->view_point[0], proj->view_point[1], proj->view_point[2]);
}
