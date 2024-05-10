#ifndef DRAW_LINE_H
#define DRAW_LINE_H

#include "../include/png_objects.h"

void draw_line(info_line line, struct Png *png);

int check_line(info_line *line);

void set_start_cords(char *xy, info_line *line);

void set_end_cords(char *xy, info_line *line);

void set_color_line(char *rgb, info_line *line);

void set_thickness_line(char *thickness, info_line *line);

#endif