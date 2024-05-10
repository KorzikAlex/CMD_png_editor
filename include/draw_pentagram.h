#ifndef DRAW_PENTAGRAM_H
#define DRAW_PENTAGRAM_H

#include "../include/png_objects.h"

void draw_pentagram(info_pentagram pentagram, struct Png *png);
int check_pentagram(info_pentagram *pentagram);
void set_radius(char *radius, info_pentagram *pentagram);
void set_center(char *center, info_pentagram *pentagram);
void set_color_pentagram(char *color, info_pentagram *pentagram);
void set_thickness_pentagram(char *thickness, info_pentagram *pentagram);

#endif