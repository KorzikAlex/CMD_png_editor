#ifndef PNG_OBJECTS
#define PNG_OBJECTS
#include <png.h>
struct Png
{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
};

typedef struct info_file
{
    char *input_file;
    char *output_file;
} info_file;

typedef struct info_line
{
    int p;
    int x1, y1, x2, y2;
    int r, g, b;
    int thickness;
} info_line;

typedef struct info_mirror
{
    int p;
    char axis;
    int x1, y1, x2, y2;
} info_mirror;

typedef struct info_pentagram
{
    int p;
    int x, y;
    int radius;
    int thickness;
    int r, g, b;
} info_pentagram;

#endif