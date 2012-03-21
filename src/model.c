#include "model.h"
#include "object.h"

static const int BUFFER_SIZE = 256;

int model_init(FILE *in, model_t *model) {
    obj_t     *new              = NULL; // The new object.
    int       return_code       = 0;    // If we parsed correctly.
    char      buf[BUFFER_SIZE];         // Our input buffer.
    object_id obj_type;                 // The type of the incoming object.



    return return_code;
}
