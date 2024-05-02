#include <stdio.h>
#include <png.h>

#include "../include/draw_pentagram.h"
#include "../include/png_objects.h"

void draw_pentagram(info_pentagram pentagram_obj, struct Png *png_object)
{
    return;
}

int check_pentagram(info_pentagram *pentagram_obj)
{
    if (!pentagram_obj->radius)
    {
        return 0;
    }
    if (!pentagram_obj->center.x || !pentagram_obj->center.y) {}
    {
        return 0;
    }
    if (!pentagram_obj->thickness) {
        return 0;
    }
    return 1;
}