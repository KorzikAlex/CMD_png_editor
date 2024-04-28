#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <png.h>
#include <string.h>
#include <ctype.h>

#include "../include/png_objects.h"
#include "../include/read_write.h"
#include "../include/print_help_info.h"
#include "../include/draw_line.h"
#include "../include/draw_pentagram.h"
#include "../include/draw_mirror.h"
#include "../include/add_operations.h"

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
        {"center", required_argument, NULL, 'q'},
        {"radius", required_argument, NULL, 'd'},
        {0, 0, 0, 0}};

    info_file information = {.output_file = "out.png", .info = 0};
    info_line line;
    info_mirror mirror;
    info_pentagram pentagram;
    // char order[3] = {0, 0, 0};

    int opt;
    int option_index = 0;

    struct Png input_image;
    if (argc == 1)
    {
        printHelp();
        return 0;
    }
    while ((opt = getopt_long(argc, argv, "hi:o:", long_opt, &option_index)) != -1)
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
            information.info = 1;
            break;
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
            break;
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
            break;
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
            break;
        }
        case 'a':
        {
            char *axis = optarg;
            if (axis == "x")
            {
                mirror.axis = 'x';
            }
            else if (axis == "y")
            {
                mirror.axis = 'y';
            }
            else
            {
                printf("Incorrect axis!\n");
                exit(0);
            }
            break;
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
            break;
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
            break;
        }
        case 't':
        {
            char *t = optarg;
            if ((t == NULL))
            {
                printf("Incorrect thickness!\n");
                exit(0);
            }
            if (is_digit(t))
            {
                line.thickness = atoi(t);
            }
            else
            {
                printf("Incorrect thickness!\n");
                exit(0);
            }
            break;
        }
        case 'd':
        {
            if (is_digit(optarg))
            {
                pentagram.radius = atoi(optarg);
            }
            else
            {
                printf("Incorrect radius!\n");
                exit(0);
            }
            break;
        }
        }
    }
    if (!information.input_file)
    {
        if (optind < argc)
        {
            information.input_file = argv[argc - 1];
        }
        else
        {
            printf("You don't specify input file!\n");
            exit(0);
        }
    }
    read_png_file(information.input_file, &input_image);
    if (information.info == 1)
    {
        printInfo(information.input_file, &input_image);
        return 0;
    }
    if (line.p == 1)
    {
        if (line.x1 && line.y1 && line.x2 && line.y2 && line.r && line.g && line.b && line.thickness) {
            draw_line(line, &input_image);
        }
        else {
            printf("You don't specify all parameters!\n");
            exit(0);
        }
    }
    if (mirror.p == 1)
    {
        draw_mirror(mirror, &input_image);
    }
    if (pentagram.p == 1)
    {
        draw_pentagram(pentagram, &input_image);
    }
    write_png_file(information.output_file, &input_image);
    return 0;
}
