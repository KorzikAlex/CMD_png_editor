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

void set_pixel(Png *png, Point p, RGB color);

RGB get_color(Point p, Png *png);

#endif