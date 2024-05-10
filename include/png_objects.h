/**
 * \file png_objects.h
 * \brief Заголовочный файл структур
 *
 * \details Содержит структуры для хранения координат точки, цвета, информации об изображении, файлах ввода и вывода,
 * линии, отражённой области и пентаграммы.
 */

#ifndef PNG_OBJECTS
#define PNG_OBJECTS

#include <png.h>

/*!
 * \struct Point
 * \brief Структура для хранения координат точки
 * \details Содержит координаты точки в виде целых чисел.
 */
typedef struct Point {
    int x;
    int y;
} Point;

typedef struct RGB {
    int r;
    int g;
    int b;
} RGB;

#pragma pack(push, 1)
struct Png {
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
};
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct info_file {
    int info;
    char *input_file;
    char *output_file;
} info_file;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct info_line {
    Point p0, p1;
    RGB color;
    int p;
    int thickness;
} info_line;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct info_mirror {
    Point p0, p1;
    int p;
    char axis;
} info_mirror;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct info_pentagram {
    Point center;
    RGB color;
    int p;
    int radius;
    int thickness;
} info_pentagram;
#pragma pack(pop)

#endif