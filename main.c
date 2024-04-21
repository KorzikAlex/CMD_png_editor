#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
#include <getopt.h>
#include <png.h>
#include <string.h>
#include <ctype.h>

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
struct Png
{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
};

typedef struct info_file
{
    char *input_file;
    char *output_file;
} info_file;

typedef struct info_line
{
    int p;
    int x1, y1, x2, y2;
    int r, g, b;
    int thickness;
} info_line;

typedef struct info_mirror
{
    int p;
    char axis;
    int x1, y1, x2, y2;
} info_mirror;

typedef struct info_pentagram
{
    int p;
    int x, y;
    int radius;
    int thickness;
    int r, g, b;
} info_pentagram;

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

void read_png_file(char *file_name, struct Png *image)
{
    int x, y;
    FILE *fp = fopen(file_name, "rb");
    char header[8];
    if (!fp)
    {
        printf("File \"%s\" not found!\n", file_name);
        exit(40);
    }
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
    {
        printf("Probably, file \"%s\" is not a png!\n", file_name);
        fclose(fp);
        exit(0);
    }
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr)
    {
        printf("Error in png structure!\n");
        exit(0);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr)
    {
        printf("Error in png info-structure (information is broken)!\n");
        png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
        exit(0);
    }
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        printf("error in png setjmp\n");
        png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
        exit(0);
    }

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);

    png_read_update_info(image->png_ptr, image->info_ptr);
    image->row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * image->height);
    for (y = 0; y < image->height; y++)
    {
        image->row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    }
    png_read_image(image->png_ptr, image->row_pointers);
    fclose(fp);
}
void write_png_file(char *file_name, struct Png *image)
{
    int x, y;
    FILE *fp = fopen(file_name, "wb");
    if (!fp)
    {
        printf("The file \"%s\" cannot be created!\n", file_name);
        exit(0);
    }
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr)
    {
        printf("It\'s impossible to write the structure of file \"%s\"!\n", file_name);
        exit(0);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr)
    {
        printf("It\'s impossible to write the information of file \"%s\"!\n", file_name);
        png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
        exit(0);
    }
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
    }
    png_init_io(image->png_ptr, fp);
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
    }
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        // printf("Something went wrong!\n");
        // free_png(image);
        // exit(0);
    }
    png_write_image(image->png_ptr, image->row_pointers);
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        // printf("Something went wrong!\n");
        // free_png(image);
        // exit(0);
    }
    png_write_end(image->png_ptr, NULL);
    for (y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    printf("Course work for option 4.20, created by Alexander Korshkov\n");
    struct option long_opt[] = {
        {"help", no_argument, NULL, 'h'},
        {"info", no_argument, NULL, '!'},

        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},

        {"line", no_argument, NULL, 'l'},
        {"start", required_argument, NULL, 's'},
        {"end", required_argument, NULL, 'e'},
        {"color", required_argument, NULL, 'c'},
        {"thickness", required_argument, NULL, 't'},

        {"mirror", no_argument, NULL, 'm'},
        {"axis", required_argument, NULL, 'a'},
        {"left_up", required_argument, NULL, 'u'},
        {"right_down", required_argument, NULL, 'r'},

        {"pentagram", no_argument, NULL, 'p'},
        {"center", required_argument, NULL, 't'},
        {"radius", required_argument, NULL, 'd'},
        {0, 0, 0, 0}};

    info_file information;
    info_line line;
    info_mirror mirror;
    info_pentagram pentagram;
    char order[3] = {0, 0, 0};

    int opt;
    int option_index = 0;

    char *input_file;
    struct Png input_image;
    char *output_file;

    while ((opt = getopt_long(argc, argv, "hi:o:", long_opt, NULL)) != -1)
    {
        switch (opt)
        {
        case 'h':
        {
            printHelp();
            break;
        }
        case '!':
        {
            printInfo(input_file, &input_image);
            return 0;
        }
        case 'i':
        {
            information.input_file = optarg;
            break;
        }
        case 'o':
        {
            information.output_file = optarg;
            break;
        }
        case 'l':
        {
            line.p = 1;
            break;
        }
        case 'm':
        {
            mirror.p = 1;
            break;
        }
        case 'p':
        {
            pentagram.p = 1;
            break;
        }
        case 's':
        {
            char *xy = optarg;
            char *x = strtok(xy, ".");
            char *y = strtok(NULL, ".");
            if ((x == NULL) || (y == NULL))
            {
                printf("Incorrect coordinates!\n");
                exit(0);
            }
            if (is_digit(x) && is_digit(y))
            {
                line.x1 = atoi(x);
                line.y1 = atoi(y);
            }
            else
            {
                printf("Incorrect coordinates!\n");
                exit(0);
            }
        }
        case 'e':
        {
            char *xy = optarg;
            char *x = strtok(xy, ".");
            char *y = strtok(NULL, ".");
            if ((x == NULL) || (y == NULL))
            {
                printf("Incorrect coordinates!\n");
                exit(0);
            }
            if (is_digit(x) && is_digit(y))
            {
                line.x2 = atoi(x);
                line.y2 = atoi(y);
            }
            else
            {
                printf("Incorrect coordinates!\n");
                exit(0);
            }
        }
        case 'c':
        {
            char *rgb = optarg;
            char *r = strtok(rgb, ".");
            char *g = strtok(NULL, ".");
            char *b = strtok(NULL, ".");
            if ((r == NULL) || (g == NULL) || (b == NULL))
            {
                printf("Incorrect color!\n");
                exit(0);
            }
            if (is_digit(r) && is_digit(g) && is_digit(b))
            {
                line.r = atoi(r);
                line.g = atoi(g);
                line.b = atoi(b);
            }
            else
            {
                printf("Incorrect color!\n");
                exit(0);
            }
        }
        case 'a':
        {
            char *axis = optarg;
            if (axis == 'x')
            {
                mirror.axis = 'x';
            }
            else if (axis == 'y')
            {
                mirror.axis = 'y';
            }
            else
            {
                printf("Incorrect axis!\n");
                exit(0);
            }
        }
        case 'u':
        {
            char *xy = optarg;
            char *x = strtok(xy, ".");
            char *y = strtok(NULL, ".");
            if ((x == NULL) || (y == NULL))
            {
                printf("Incorrect coordinates!\n");
                exit(0);
            }
            if (is_digit(x) && is_digit(y))
            {
                mirror.x1 = atoi(x);
                mirror.y1 = atoi(y);
            }
            else
            {
                printf("Incorrect coordinates!\n");
                exit(0);
            }
        }
        case 'r':
        {
            char *xy = optarg;
            char *x = strtok(xy, ".");
            char *y = strtok(NULL, ".");
            if ((x == NULL) || (y == NULL))
            {
                printf("Incorrect coordinates!\n");
                exit(0);
            }
            if (is_digit(x) && is_digit(y))
            {
                mirror.x2 = atoi(x);
                mirror.y2 = atoi(y);
            }
            else
            {
                printf("Incorrect coordinates!\n");
                exit(0);
            }
        }
        case 't': {
            char *xy = optarg;
            char *x = strtok(xy, ".");
            char *y = strtok(NULL, ".");
            if ((x == NULL) || (y == NULL))
            {
                printf("Incorrect coordinates!\n");
                exit(0);
            }
            if (is_digit(x) && is_digit(y))
            {
                mirror.x1 = atoi(x);
                mirror.y1 = atoi(y);
            }
            else
            {
                printf("Incorrect coordinates!\n");
                exit(0);
            }
        }
        case 'd': {
            if (is_digit(optarg)) {
                pentagram.radius = atoi(optarg);
            }
            else {
                printf("Incorrect radius!\n");
                exit(0);
            }
        }
        }
    }
    return 0;
}
