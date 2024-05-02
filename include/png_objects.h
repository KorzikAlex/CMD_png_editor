#ifndef PNG_OBJECTS
#define PNG_OBJECTS
#include <png.h>

typedef struct Point {
    int x, y;
} Point;

typedef struct RGB {
    int r, g, b;
} RGB;

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
    int info;
} info_file;

typedef struct info_line
{
    int p;
    Point p0, p1;
    RGB color;
    int thickness;
} info_line;

typedef struct info_mirror
{
    int p;
    char axis;
    Point p0, p1;
} info_mirror;

typedef struct info_pentagram
{
    int p;
    Point center;
    int radius;
    int thickness;
    
} info_pentagram;

#endif