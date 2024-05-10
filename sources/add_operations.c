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
void free_png(struct Png *png) {
    int y;
    if (png->row_pointers != NULL) {
        for (y = 0; y < png->height; y++) {
            free(png->row_pointers[y]);
        }
    }
    free(png->row_pointers);
    if (png->png_ptr != NULL && png->info_ptr != NULL) {
        png_destroy_read_struct(&png->png_ptr, &png->info_ptr, NULL);
    }
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
};