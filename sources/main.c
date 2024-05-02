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

    struct Png input_image;

    info_file information = {.output_file = "out.png", .info = 0};
    info_line line = {.p = 0};
    info_mirror mirror = {.p = 0};
    info_pentagram pentagram = {.p = 0};

    int opt;

    if (argc == 1)
    {
        printHelp();
        return 0;
    }
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
                line.p0.x = atoi(x);
                line.p0.y = atoi(y);
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
                line.p1.x = atoi(x);
                line.p1.y = atoi(y);
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
                line.color.r = atoi(r);
                line.color.g = atoi(g);
                line.color.b = atoi(b);
            }
            else
            {
                printf("Incorrect color!\n");
                exit(41);
            }
            break;
        }
        case 'a':
        {
            char *axis = optarg;
            if (strcmp(axis, "x") == 0)
            {
                mirror.axis = 'x';
            }
            else if (strcmp(axis, "y") == 0)
            {
                mirror.axis = 'y';
            }
            else
            {
                printf("Incorrect axis!\n");
                exit(41);
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
                mirror.p0.x = atoi(x);
                mirror.p0.y = atoi(y);
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
                mirror.p1.x = atoi(x);
                mirror.p1.y = atoi(y);
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
            if (t == NULL)
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
            exit(40);
        }
    }
    read_png_file(information.input_file, &input_image);
    if (information.info == 1)
    {
        printInfo(information.input_file, &input_image);
        return 0;
    }
    if (line.p)
    {
        if (check_line(&line))
        {
            draw_line(line, &input_image);
        }
        else
        {
            printf("You don't specify all parameters for line!\n");
            free_png(&input_image);
            exit(40);
        }
    }
    if (mirror.p)
    {
        if (check_mirror(&mirror))
        {
            draw_mirror(mirror, &input_image);
        }
        else
        {
            printf("You don't specify all parameters for mirror!\n");
            free_png(&input_image);
            exit(40);
        }
    }
    if (pentagram.p)
    {
        if (check_pentagram(&pentagram))
        {
            draw_pentagram(pentagram, &input_image);
        }
        else
        {
            printf("You don't specify all parameters for Pentagram!\n");
            free_png(&input_image);
            exit(40);
        }
    }
    write_png_file(information.output_file, &input_image);
    return 0;
}
