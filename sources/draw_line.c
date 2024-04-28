#include <stdio.h>
#include <png.h>

#include "../include/draw_line.h"
#include "../include/png_objects.h"

void draw_line(info_line line_obj, struct Png *png_object) {
    int x, y;
    if (png_get_color_type(png_object->png_ptr, png_object->info_ptr) == PNG_COLOR_TYPE_RGB)
    {
        printf("input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA");
    }

    else if (png_get_color_type(png_object->png_ptr, png_object->info_ptr) != PNG_COLOR_TYPE_RGBA)
    {
        printf("color_type of input file must be PNG_COLOR_TYPE_RGBA");
    }
    for (y = 0; y < png_object->height; y++)
    {
        png_byte *row = png_object->row_pointers[y];
        for (x = 0; x < png_object->width; x++)
        {
            png_byte *ptr = &(row[x * 4]);
        }
    }
}
    