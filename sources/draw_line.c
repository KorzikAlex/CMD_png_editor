#include <stdio.h>
#include <png.h>
#include <stdlib.h>

#include "../include/draw_line.h"
#include "../include/png_objects.h"

void draw_line(info_line line_obj, struct Png *png_object) {
    int dx, dy;
    dx = abs(line_obj.x2 - line_obj.x1);
    dy = abs(line_obj.y2 - line_obj.y1);

    if (png_get_color_type(png_object->png_ptr, png_object->info_ptr) == PNG_COLOR_TYPE_RGB)
    {
        printf("input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA");
    }

    else if (png_get_color_type(png_object->png_ptr, png_object->info_ptr) != PNG_COLOR_TYPE_RGBA)
    {
        printf("color_type of input file must be PNG_COLOR_TYPE_RGBA");
    }
    double k = (double)(dy / dx);
    for (int i = 0; i <= dx; i++) {
        int x = line_obj.x1 + i;
        int y = line_obj.y1 + i * k;
        
    }
}
    