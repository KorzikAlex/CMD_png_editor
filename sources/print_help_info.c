#include <stdio.h>
#include <stdlib.h>

#include "../include/png_objects.h"
#include "../include/print_help_info.h"

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

void printInfo(char *input_file, struct Png *png)
{
    if (png == NULL)
    {
        printf("Error: PNG file \"%s\" isn't initialized\n", input_file);
        return;
    }
    printf("Information about PNG file \"%s\":\n", input_file);
    printf("Width: %d\n", png->width);
    printf("Height: %d\n", png->height);

    printf("Color type: %d\n", png->color_type);
    printf("Bit depth: %d\n", png->bit_depth);

    printf("Number of passes: %d\n", png->number_of_passes);
    free_png(png);
}

void printHelp()
{
    printf("Usage: program_name [OPTIONS]\n");
    printf("Options:\n");
    printf("-h, --help - print information about flags\n");
    printf("--info - print information about PNG file\n");
    printf("-i, --input - set input file name\n");
    printf("-o, --output - set output file name\n");
    // printf("-c, --color - set color type\n");
    // printf("-b, --bit - set bit depth\n");
}