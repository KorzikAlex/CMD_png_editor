#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "../include/add_operations.h"
#include "../include/png_objects.h"

int is_digit(char *line)
{
    if (strlen(line) == 0)
    {
        return 0;
    }
    for (int i = 0; i < strlen(line); i++)
    {
        if (!isdigit(line[i]))
        {
            return 0;
        }
    }
    return 1;
}

void set_pixel(struct Png* image, Point p, Pixel color)
{
    int index;
    if (p.x >= 0 && p.x < image->header.width_px && p.y >= 0 && p.y < image->header.height_px) {
        index = ((image->header.height_px - p.y - 1) * image->header.width_px + p.x) * 3;
        image->data[index + 2] = color.red;
        image->data[index] = color.blue;
        image->data[index + 1] = color.green;
    }
}