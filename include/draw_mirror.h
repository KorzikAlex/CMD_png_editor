#ifndef DRAW_MIRROR_H
#define DRAW_MIRROR_H

#include "../include/png_objects.h"

void draw_mirror(Point p0, Point p1, char axis, Png *png);

int check_mirror(info_mirror *mirror);

void set_left_up(char *xy, info_mirror *mirror);

void set_right_down(char *xy, info_mirror *mirror);

void set_axis(char *axis, info_mirror *mirror);

#endif