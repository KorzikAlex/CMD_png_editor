#ifndef DRAW_MIRROR_H
#define DRAW_MIRROR_H

#include "../include/png_objects.h"

void draw_mirror(info_mirror mirror_obj, struct Png *png_object);
int check_mirror(info_mirror *mirror_obj);

#endif