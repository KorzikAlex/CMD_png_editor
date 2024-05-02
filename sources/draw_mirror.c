#include <stdio.h>
#include <png.h>

#include "../include/draw_mirror.h"
#include "../include/png_objects.h"

void draw_mirror(info_mirror mirror_obj, struct Png *png_object) {
    return;
}

int check_mirror(info_mirror *mirror_obj) {
    if (!mirror_obj->p0.x || !mirror_obj->p0.y) {
        return 0;
    }
    if (!mirror_obj->axis) {
        return 0;
    }
    return 1;
}