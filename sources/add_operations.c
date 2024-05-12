#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../include/add_operations.h"
#include "../include/png_objects.h"

/* проверка, что строка является числом */
int is_digit(char *line) {
    if (strlen(line) == 0) {
        return 0;
    }
    for (int i = 0; i < strlen(line); i++) {
        if (!isdigit(line[i])) {
            return 0;
        }
    }
    return 1;
}

/* освобождение памяти от изображения */
void free_png(Png *png) {
    int y;
    for (y = 0; y < png->height; y++)
        free(png->row_pointers[y]);
    free(png->row_pointers);
    png_destroy_read_struct(&png->png_ptr, &png->info_ptr, NULL);
}

void check_color(info_line *line_obj) {
    if (line_obj->color.r < 0 || line_obj->color.r > 255) {
        puts("Your RED (R) color isn't correct (must be between 0 and 255)");
        exit(42);
    }
    if (line_obj->color.g < 0 || line_obj->color.g > 255) {
        puts("Your GREEN (G) color isn't correct (must be between 0 and 255)");
        exit(42);
    }
    if (line_obj->color.b < 0 || line_obj->color.b > 255) {
        puts("Your BLUE (B) color isn't correct (must be between 0 and 255)");
        exit(42);
    }
}

void set_pixel(Png *png, Point p, RGB color) {
    if (p.x >= 0 && p.x < png->width && p.y >= 0 && p.y < png->height) {
        png_byte *ptr = &(png->row_pointers[p.y][p.x * 4]);
        ptr[0] = color.r;
        ptr[1] = color.g;
        ptr[2] = color.b;
    }
}

RGB get_color(Point p, Png *png) {
    png_byte *ptr = &(png->row_pointers[p.y][p.x * 4]);
    RGB color = {.r=ptr[0], .g=ptr[1], .b=ptr[2]};
    return color;
}