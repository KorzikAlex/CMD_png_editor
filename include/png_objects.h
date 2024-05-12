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
 */
#pragma pack(push, 1)
typedef struct Png {
    int width; /**< Ширина изображения */
    int height; /**< Высота изображения */
    png_byte color_type; /**< Тип цвета */
    png_byte bit_depth; /**< Глубина цвета */

    png_structp png_ptr; /**< Указатель на структуру PNG изображения */
    png_infop info_ptr; /**< Указатель на структуру для хранения информации о PNG изображении */
    int number_of_passes; /**< Количество проходов по изображению */
    png_bytep *row_pointers; /**< Указатель на структуру для хранения строк */
} Png;
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
    Point p0;
    Point p1;
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
    Point p0;
    Point p1;
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