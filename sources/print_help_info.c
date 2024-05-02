#include <stdio.h>
#include <stdlib.h>

#include "../include/png_objects.h"
#include "../include/print_help_info.h"
#include "../include/add_operations.h"

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
    free_png(png);
}

void printHelp()
{
    printf("Usage: program_name [OPTIONS]\n");
    printf("Options:\n");
    printf("-h, --help - print information about flags\n");
    printf("--info - print information about PNG file\n");
    printf("-i, --input <argument> - set input file name\n");
    printf("-o, --output <argument> - set output file name\n");
}