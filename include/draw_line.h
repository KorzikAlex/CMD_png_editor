/**
 * \file draw_line.h
 * \brief Заголовочный файл с функциями рисования линии
 * \details В данном заголовочном файле описаны функции для настройки параметров линии и её отрисовки
 */
#ifndef DRAW_LINE_H
#define DRAW_LINE_H

#include "../include/png_objects.h"

/**
 *
 * \brief Функция, которая рисует линию
 * \param [in]
 * \param [out] png
 * \details Принимает на вход две точки, цвет, , содержащую изображение и рисует линию.
 * \param [in] p0
 * \param [in] p1
 * \param [in] color
 * \param [in] thickness
 * \param [out] png
 */
void draw_line(Point p0, Point p1, RGB color, int thickness, Png *png);

/**
 * \brief Функция, проверяющая наличие всех аргументов линии
 * \param [in] line
 * \details Принимает структуру с информацией о линии, затем проверяет, что все аргументы были введены.
 * \return 1, если есть все необходимые аргументы, иначе 0
 */
int check_line(info_line *line);

/**
 * \brief Функция, которая задаёт стартовые координаты
 * \param [in] xy
 * \param [out] line
 * \details Принимает указатель на строку координатами и структуру с информацией о линии, задаёт начальные координаты.
 */
void set_start_cords(char *xy, info_line *line);

/**
 * \brief Функция, которая задаёт конечные координаты
 * \param [in] xy
 * \param [out] line
 * \details Принимает указатель на строку c координатами x.y и структуру с информацией о линии, задаёт конечные координаты.
 */
void set_end_cords(char *xy, info_line *line);

/**
 * \brief Функция, которая задаёт стартовые координаты
 * \param [in] rgb
 * \param [out] line
 * \details Принимает указатель на строку с цветом вида r.g.b и структуру с информацией о линии, задаёт цвет линии.
 */
void set_color_line(char *rgb, info_line *line);

/**
 * \brief Функция, которая задаёт стартовые координаты
 * \param [in] thickness
 * \param [out] line
 * \details Принимает указатель на строку c толщиной линии и структуру с информацией о линии, задаёт толщину линии.
 */
void set_thickness_line(char *thickness, info_line *line);

#endif