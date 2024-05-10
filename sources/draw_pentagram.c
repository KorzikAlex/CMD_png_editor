#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

#include "../include/draw_pentagram.h"
#include "../include/png_objects.h"
#include "../include/add_operations.h"

void draw_pentagram(info_pentagram pentagram, struct Png *png) {
    return;
}

int check_pentagram(info_pentagram *pentagram) {
    if (!pentagram->radius) {
        puts("You don't specify radius of pentagram!");
        return 0;
    }
    if (!pentagram->center.x || !pentagram->center.y) {
        puts("You don't specify center of pentagram!");
        return 0;
    }
    if (!pentagram->thickness) {
        puts("You don't specify thickness of pentagram!");
        return 0;
    }
    return 1;
}

void set_radius(char *radius, info_pentagram *pentagram) {
    if (radius == NULL) {
        printf("You don't specify radius of pentagram!\n");
        exit(41);
    }
    if (is_digit(radius)) {
        pentagram->radius = atoi(radius);
    } else {
        printf("Your pentagram's radius isn't an integer number!\n");
        exit(0);
    }
}

void set_center(char *center, info_pentagram *pentagram) {
    char *x = strtok(center, ".");
    char *y = strtok(NULL, ".");
    if (x == NULL) {
        puts("You don't specify X for center of pentagram!");
        exit(40);
    }
    if (y == NULL) {
        puts("You don't specify Y for center of pentagram!");
        exit(40);
    }
    if (is_digit(x))
        pentagram->center.x = atoi(x);
    else {
        puts("Your X coord for pentagram's center isn't integer number!");
        exit(41);
    }
    if (is_digit(y)) {
        pentagram->center.y = atoi(y);
    } else {
        puts("Your Y coord for pentagram's center isn't integer number!");
        exit(41);
    }
}

void set_thickness_pentagram(char *thickness, info_pentagram *pentagram) {
    if (thickness == NULL) {
        printf("You don't specify thickness of pentagram!\n");
        exit(40);
    }
    if (is_digit(thickness)) {
        pentagram->thickness = atoi(thickness);
    } else {
        printf("Your pentagram's thickness isn't integer number!\n");
        exit(40);
    }
}

void set_color_pentagram(char *rgb, info_pentagram *pentagram) {
    char *r = strtok(rgb, ".");
    char *g = strtok(NULL, ".");
    char *b = strtok(NULL, ".");
    if (r == NULL) {
        puts("You don't specify R (red) component of pentagram's color!");
        exit(40);
    }
    if (g == NULL) {
        puts("You don't specify G (green) component of pentagram's color!");
        exit(40);
    }
    if (b == NULL) {
        puts("You don't specify B (blue) component of pentagram's color!");
        exit(40);
    }
    if (is_digit(r))
        pentagram->color.r = atoi(r);
    else {
        puts("Your R component of pentagram's color isn't integer number!");
        exit(41);
    }
    if (is_digit(g))
        pentagram->color.g = atoi(g);
    else {
        puts("Your G component of pentagram's color isn't integer number!");
        exit(41);
    }
    if (is_digit(b))
        pentagram->color.b = atoi(b);
    else {
        puts("Your B component of pentagram's color isn't integer number!");
        exit(41);
    }
}