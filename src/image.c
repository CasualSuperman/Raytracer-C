#include <math.h>
#include <stdlib.h>

#include "Alloc.h"
#include "log.h"

#include "image.h"
#include "model.h"
#include "projection.h"
#include "raytracer.h"
#include "vector.h"

static void print_header(int, int);
static pixel_t* pos_to_pixel(int, int, int, pixel_t *);

void make_image(model_t *model) {
    proj_t  *proj  = model->proj;
    int     width  = proj->win_size_pixel[0];
    int     height = proj->win_size_pixel[1];
    pixel_t *image = Malloc((size_t) (width * height) * sizeof(pixel_t));
    int     col    = 0;
    size_t  count  = 0;

    // Loop through the pixels.
    for (; col < height; ++col) {
        int row = 0;
        for (; row < width; ++row) {
            make_pixel(model, row, col, pos_to_pixel(row, col, width, image));
        }
    }

    // Give them the image.
    print_header(width, height);
    count = fwrite(image, sizeof(pixel_t), (size_t) (height * width), stdout);

    // Make sure we wrote everything. Also use our return value.
    if (count < (unsigned long) (width * height)) {
        say("Warning: Not all image bytes may have been written.");
    }

    // Free our pixel map.
    Free(image);
}

void make_pixel(model_t *model, int row, int col, pixel_t *pix) {
    double dir[3]   = {0, 0, 0};
    double base[3]  = {0, 0, 0};
    double color[3] = {0, 0, 0};
    int i;

    map_pixel_to_world(model->proj, row, col, base);

    diffN(model->proj->view_point, base, dir, 3);
    unitvecN(dir, dir, 3);

#if defined DEBUG_RAY || defined DEBUG_PIXEL
    say("");

    say("Tracing pixel %d, %d. - %lf %lf (direction %lf %lf %lf)", row, col,
        base[0], base[1],
        dir[0], dir[1], dir[2]);
#endif
    ray_trace(model, model->proj->view_point, dir, color, 0.0, NULL);

    for (i = 0; i < 3; ++i) {
        if (color[i] > 1) {
            color[i] = 1;
        }
    }

#ifdef DEBUG_PIXEL
    say("Pixel color: #%02hhx%02hhx%02hhx", color[0], color[1], color[2]);
#endif

    pix->r = (unsigned char) (color[0] * 255);
    pix->g = (unsigned char) (color[1] * 255);
    pix->b = (unsigned char) (color[2] * 255);
}

static void print_header(int width, int height) {
    printf("P6");
    printf("\n");
    printf("%d %d", width, height);
    printf("\n");
    printf("255");
    printf("\n");
    fflush(stdout);
}

static inline pixel_t* pos_to_pixel(int row, int col, int height, pixel_t *base) {
    return (col * height + row) + base;
}
