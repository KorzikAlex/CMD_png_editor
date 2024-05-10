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

/*!
 * \struct RGB
 * \brief Структура для цвета
 * \details Содержит цвет в формате rgb в виде целых чисел.
 */
typedef struct RGB {
    int r;
    int g;
    int b;
} RGB;

/*!
 * \struct Png
 * \brief Структура для информации о PNG изображении.
 * \details Содержит информацию об изображении.
 * \var width - ширина изображения
 *
 * \var height - высота изображения
 * \var color_type - тип цвета
 * \var bit_depth - глубина цвета
 * \var png_ptr - указатель на структуру для хранения информации о PNG изображении
 * \var info_ptr - указатель на структуру для хранения информации о PNG изображении
 * \var number_of_passes - количество проходов по изображению
 * \var row_pointers - указатель на структуру для хранения строк.
 */
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

/*!
 * \struct info_file
 * \brief Структура для хранения информации о файле ввода
 * \details Содержит информацию о файле ввода.
 * \var input_file - имя файла ввода
 * \var output_file - имя файла вывода
 * \var info - вывод информации об изображении
 */
#pragma pack(push, 1)
typedef struct info_file {
    int info;
    char *input_file;
    char *output_file;
} info_file;
#pragma pack(pop)

/*!
 * \struct info_line
 * \brief Структура для хранения информации о линии
 * \details Содержит информацию о линии.
 * \var p - отвечает за отрисовку линии
 * \var p0 - начальная точка линии
 * \var p1 - конечная точка линии
 * \var color - цвет линии
 * \var thickness - толщина линии
 */
#pragma pack(push, 1)
typedef struct info_line {
    Point p0, p1;
    RGB color;
    int p;
    int thickness;
} info_line;
#pragma pack(pop)

/*!
 * \struct info_mirror
 * \brief Структура для хранения информации об отражённой области
 * \details Содержит информацию об отражённой области.
 * \var p - отвечает за отрисовку отражённой области
 * \var p0 - верхний левый угол отражённой области
 * \var p1 - нижний правый угол отражённой области
 * \var axis - ось отражённой области
 */
#pragma pack(push, 1)
typedef struct info_mirror {
    Point p0, p1;
    int p;
    char axis;
} info_mirror;
#pragma pack(pop)

/*!
 * \struct info_pentagram
 * \brief Структура для хранения информации об пентаграмме
 * \details Содержит информацию об пентаграмме.
 * \var p - отвечает за отрисовку пентаграммы
 * \var center - центр пентаграммы
 * \var color - цвет пентаграммы
 * \var radius - радиус пентаграммы
 * \var thickness - толщина пентаграммы
 */
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