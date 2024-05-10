#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

#include "../include/draw_mirror.h"
#include "../include/png_objects.h"
#include "../include/add_operations.h"

/* функция отражения области */
void draw_mirror(info_mirror mirror, struct Png *png) {
    return;
}

int check_mirror(info_mirror *mirror) {
    if (mirror->p0.x == -1 || mirror->p0.y == -1) {
        puts("You don't specify start cords of mirror's edge!");
        return 0;
    }
    if (mirror->p1.x == -1 || mirror->p1.y == -1) {
        puts("You don't specify end cords of mirror's edge!");
        return 0;
    }
    if (mirror->axis == 'n') {
        puts("You don't specify axis of mirror!");
        return 0;
    }
    return 1;
}

void set_left_up(char *xy, info_mirror *mirror) {
    char *x = strtok(xy, ".");
    char *y = strtok(NULL, ".");
    if (x == NULL) {
        puts("You don't specify X for left_up point of mirror's edge!");
        exit(40);
    }
    if (y == NULL) {
        puts("You don't specify Y for left_up point of mirror's edge!");
        exit(40);
    }
    if (is_digit(x))
        mirror->p0.x = atoi(x);
    else {
        puts("Your X coord for left_up point isn't integer number!");
        exit(41);
    }
    if (is_digit(y)) {
        mirror->p0.y = atoi(y);
    } else {
        puts("Your Y coord for left_up point isn't integer number!");
        exit(41);
    }
}

void set_right_down(char *xy, info_mirror *mirror) {
    char *x = strtok(xy, ".");
    char *y = strtok(NULL, ".");
    if (x == NULL) {
        puts("You don't specify X for right_down point of mirror's edge!");
        exit(40);
    }
    if (y == NULL) {
        puts("You don't specify Y for right_down point of mirror's edge!");
        exit(40);
    }
    if (is_digit(x))
        mirror->p1.x = atoi(x);
    else {
        puts("Your X coord for right_down point isn't integer number!");
        exit(41);
    }
    if (is_digit(y)) {
        mirror->p1.y = atoi(y);
    } else {
        puts("Your Y coord for right_down point isn't integer number!");
        exit(41);
    }
}

void set_axis(char *axis, info_mirror *mirror) {
    if (strcmp(axis, "x") == 0) {
        mirror->axis = 'x';
    } else if (strcmp(axis, "y") == 0) {
        mirror->axis = 'y';
    } else {
        puts("Your axis isn't 'x' or 'y'!");
        exit(41);
    }
}