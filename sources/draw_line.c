#include <stdio.h>
#include <string.h>
#include <png.h>
#include <stdlib.h>

#include "../include/draw_line.h"
#include "../include/png_objects.h"
#include "../include/add_operations.h"

/* функция для рисования линия */
void draw_line(Point p0, Point p1, RGB color, int thickness, Png *png) {
    if (png_get_color_type(png->png_ptr, png->info_ptr) == PNG_COLOR_TYPE_RGB) {
        printf("input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA");
        exit(46);
    } else if (png_get_color_type(png->png_ptr, png->info_ptr) != PNG_COLOR_TYPE_RGBA) {
        printf("color_type of input file must be PNG_COLOR_TYPE_RGBA");
        exit(46);
    }
    int dx = abs(p1.x - p0.x);
    int dy = abs(p1.y - p0.y);
    int sx = (p0.x < p1.x) ? 1 : -1;
    int sy = (p0.y < p1.y) ? 1 : -1;
    int err = dx - dy;
    while (p0.x != p1.x || p0.y != p1.y) {
        for (int i = -thickness / 2; i <= thickness / 2; i++) {
            for (int j = -thickness / 2; j <= thickness / 2; j++) {
                Point p = {p0.x + i, p0.y + j};
                set_pixel(png, p, color);
            }
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            p0.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            p0.y += sy;
        }
    }
}

/* проверка введённых параметров для линии на существование (все ли существуют) */
int check_line(info_line *line) {
    if (line->p0.x == -1 || line->p0.y == -1) {
        puts("You don't specify start cords of line!"); /* нет начальных координат */
        return 0;
    }
    if (line->p1.x == -1 || line->p1.y == -1) {
        puts("You don't specify end cords of line!"); /* нет конечных координат */
        return 0;
    }
    if (line->color.r == -1 || line->color.g == -1 || line->color.b == -1) {
        puts("You don't specify color of line!"); /* нет конечных координат */
        return 0;
    }
    if (line->thickness == -1) {
        puts("You don't specify thickness of line!"); /* нет толщины */
        return 0;
    }
    return 1;
}

/* функция для задания начальных координат */
void set_start_cords(char *xy, info_line *line) {
    char *x = strtok(xy, ".");
    char *y = strtok(NULL, ".");
    if (x == NULL) {
        puts("You don't specify X for start point of line!");
        exit(40);
    }
    if (y == NULL) {
        puts("You don't specify Y for start point of line!");
        exit(40);
    }
    if (is_digit(x))
        line->p0.x = atoi(x);
    else {
        puts("Your X coord for start point isn't integer number!");
        exit(41);
    }
    if (is_digit(y)) {
        line->p0.y = atoi(y);
    } else {
        puts("Your Y coord for start point isn't integer number!");
        exit(41);
    }
}

/* функция для задания конечных координат */
void set_end_cords(char *xy, info_line *line) {
    char *x = strtok(xy, ".");
    char *y = strtok(NULL, ".");
    if (x == NULL) {
        puts("You don't specify X for end point of line!");
        exit(40);
    }
    if (y == NULL) {
        puts("You don't specify Y for end point of line!");
        exit(40);
    }
    if (is_digit(x))
        line->p1.x = atoi(x);
    else {
        puts("Your X coord for end point isn't integer number!");
        exit(41);
    }
    if (is_digit(y)) {
        line->p1.y = atoi(y);
    } else {
        puts("Your Y coord for end point isn't integer number!");
        exit(41);
    }
}

/* функция для задания цвета линии */
void set_color_line(char *rgb, info_line *line) {
    char *r = strtok(rgb, ".");
    char *g = strtok(NULL, ".");
    char *b = strtok(NULL, ".");
    if (r == NULL) {
        puts("You don't specify R (red) component of line's color!");
        exit(40);
    }
    if (g == NULL) {
        puts("You don't specify G (green) component of line's color!");
        exit(40);
    }
    if (b == NULL) {
        puts("You don't specify B (blue) component of line's color!");
        exit(40);
    }
    if (is_digit(r))
        line->color.r = atoi(r);
    else {
        puts("Your R component of line's color isn't integer number!");
        exit(41);
    }
    if (is_digit(g))
        line->color.g = atoi(g);
    else {
        puts("Your G component of line's color isn't integer number!");
        exit(41);
    }
    if (is_digit(b))
        line->color.b = atoi(b);
    else {
        puts("Your B component of line's color isn't integer number!");
        exit(41);
    }
}

/* функция для задания толщины линии */
void set_thickness_line(char *thickness, info_line *line) {
    if (thickness == NULL) {
        printf("You don't specify thickness of line!\n");
        exit(40);
    }
    if (is_digit(thickness)) {
        line->thickness = atoi(thickness);
    } else {
        printf("Your line's thickness isn't integer number!\n");
        exit(40);
    }
}