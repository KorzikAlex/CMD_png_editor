/**
 * \file add_operations.h
 * \brief Заголовочный файл для дополнительных операций
 * \details Содержит описание функций
 */
#ifndef ADD_OPERATIONS_H
#define ADD_OPERATIONS_H

#include "../include/png_objects.h"

int is_digit(char *line);

void free_png(Png *png);

void check_color(info_line *line);

void set_pixel(int x, int y, RGB color, Png *png);

RGB get_color(int x, int y, Png *png);

void draw_circle(Point p, int radius, RGB color, int thickness, Png *png);

#endif