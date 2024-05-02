#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../include/add_operations.h"
#include "../include/png_objects.h"

int is_digit(char *line)
{
    if (strlen(line) == 0)
    {
        return 0;
    }
    for (int i = 0; i < strlen(line); i++)
    {
        if (!isdigit(line[i]))
        {
            return 0;
        }
    }
    return 1;
}

void free_png(struct Png *png)
{
    int y;
    if (png->row_pointers != NULL)
    {
        for (y = 0; y < png->height; y++)
        {
            free(png->row_pointers[y]);
        }
    }
    free(png->row_pointers);
    if (png->png_ptr != NULL && png->info_ptr != NULL)
    {
        png_destroy_read_struct(&png->png_ptr, &png->info_ptr, NULL);
    }
}