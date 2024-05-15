/**
 * \author KorzikAlex
 * \brief Главный файл программы CMD PNG EDITOR
 *
 * \details Главный файл программы CMD PNG EDITOR, в которой происходит обработка и вызов функций, в том числе
 * чтение и запись файла, рисование лини и пентаграмма, а также отражение области.
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "../include/png_objects.h" /* объекты и структуры для PNG */
#include "../include/read_write.h" /* функции чтения и записи файла */
#include "../include/print_help_info.h" /* функции вывода информации о программе и изображении*/
#include "../include/draw_line.h" /* функции рисования линии */
#include "../include/draw_pentagram.h" /* функции рисования пентаграммы */
#include "../include/draw_mirror.h" /* функции отражения области */
#include "../include/add_operations.h" /* дополнительных  */

/**
 * \brief  Главная функция программы
 * \param [in] argc Количество аргументов командной строки
 * \param [in] argv Массив аргументов командной строки
 * \return Код возврата
 */

int main(int argc, char *argv[]) {
    /* вывод информации о курсовой работе и авторе */
    puts("Course work for option 4.20, created by Alexander Korshkov");

    /* проверка, переданы ли аргументы */
    if (argc == 1) {
        print_help();
        return 0;
    }

    /* структура, содержащая длинная флаги */
    struct option long_opt[] = {
            {"help",       no_argument,       NULL, 'h'}, /* справка */
            {"info",       no_argument,       NULL, '!'}, /* информация о файле */

            {"input",      required_argument, NULL, 'i'}, /* входной файл */
            {"output",     required_argument, NULL, 'o'}, /* выходной файл */

            {"line",       no_argument,       NULL, 300}, /* рисование линии */
            {"start",      required_argument, NULL, 301}, /* начальная точка */
            {"end",        required_argument, NULL, 302}, /* конечная точка */
            {"color",      required_argument, NULL, 303}, /* цвет линии */
            {"thickness",  required_argument, NULL, 304}, /* толщина линии */

            {"mirror",     no_argument,       NULL, 400}, /* отражение */
            {"axis",       required_argument, NULL, 401}, /* ось отражения */
            {"left_up",    required_argument, NULL, 402}, /* верхний левый угол области */
            {"right_down", required_argument, NULL, 403}, /* нижний правый угол области */

            {"pentagram",  no_argument,       NULL, 404}, /* рисование пентаграммы в круге*/
            {"center",     required_argument, NULL, 405}, /* центр круга */
            {"radius",     required_argument, NULL, 406}, /* радиус круга */
            /* color */ /* цвет линии пентаграмма */
            /* thickness */ /* толщина линии пентаграмма */
            {0, 0, 0,                               0}
    };

    /* информация о фото */
    Png input_image;

    /* информация о входном и выходном файле */
    info_file information = {.output_file = "out.png", .info = 0};

    /* информация о линии, области для отражения и рисования пентаграммы */
    info_line line = {.p = 0, .p0 = {.x = -1, .y = -1}, .p1 = {.x = -1, .y = -1},
                      .thickness = -1, .color = {.r = -1, .g = -1, .b = -1}};
    info_mirror mirror = {.p = 0, .p0 = {.x = -1, .y = -1}, .p1 = {.x = -1, .y = -1}, .axis = 'n'};
    info_pentagram pentagram = {.p = 0, .center = {.x = -1, .y = -1}, .radius = -1};

    /* цикл, обрабатывающий флаги и аргументы */
    int opt;
    while ((opt = getopt_long(argc, argv, "hi:o:", long_opt, NULL)) != -1) {
        switch (opt) {
            /* справка */
            case 'h': {
                print_help();
                break;
            }
                /* информация о файле */
            case '!': {
                information.info = 1;
                break;
            }
                /* входной файл */
            case 'i': {
                information.input_file = optarg;
                break;
            }
                /* выходной файл */
            case 'o': {
                information.output_file = optarg;
                break;
            }
                /* рисование линии */
            case 300: {
                line.p = 1;
                break;
            }
                /* начальная координата линии */
            case 301: {
                set_start_cords(optarg, &line);
                break;
            }
                /* конечная координата линии */
            case 302: {
                set_end_cords(optarg, &line);
                break;
            }
                /* цвет линии (для пентаграммы тоже)*/
            case 303: {
                if (line.p == 1)
                    set_color_line(optarg, &line);
                if (pentagram.p == 1)
                    set_color_pentagram(optarg, &pentagram);
                break;
            }
                /* толщина линии (для пентаграммы тоже) */
            case 304: {
                if (line.p == 1)
                    set_thickness_line(optarg, &line);
                if (pentagram.p == 1)
                    set_thickness_pentagram(optarg, &pentagram);
                break;
            }
                /* отражение области */
            case 400: {
                mirror.p = 1;
                break;
            }
                /* ось отражённой области */
            case 401: {
                set_axis(optarg, &mirror);
                break;
            }
                /* верхний левый угол области */
            case 402: {
                set_left_up(optarg, &mirror);
                break;
            }
                /* нижний правый угол области */
            case 403: {
                set_right_down(optarg, &mirror);
                break;
            }
                /* рисование пентаграммы в круге */
            case 404: {
                pentagram.p = 1;
                break;
            }
                /* центр круга */
            case 405: {
                set_center(optarg, &pentagram);
                break;
            }
                /* радиус круга */
            case 406: {
                set_radius(optarg, &pentagram);
                break;
            }
        }
    }
    /* проверка, что имя файла было как-то передано (через опцию или в конце отдельным аргументом) */
    if (!information.input_file) {
        if (optind < argc) {
            information.input_file = argv[argc - 1];
        } else {
            printf("You don't specify input file!\n");
            exit(40);
        }
    }
    /* чтение и получение информации об изображении */
    read_png_file(information.input_file, &input_image);

    /* проверка, ввёл ли пользователь флаг --info */
    if (information.info == 1) {
        print_info(information.input_file, &input_image);
        free_png(&input_image);
        return 0;
    }
    /* проверка на корректность и количество введённых параметров линии */
    if (line.p) {
        if (check_line(&line))
            draw_line(line.p0, line.p1, line.color, line.thickness, &input_image);
        else {
            printf("You don't specify all parameters for line!\n");
            free_png(&input_image);
            exit(40);
        }
    }
    /* проверка на корректность и количество введённых параметров отражённой области */
    if (mirror.p) {
        if (check_mirror(&mirror))
            draw_mirror(mirror.p0, mirror.p1, mirror.axis, &input_image);
        else {
            printf("You don't specify all parameters for mirror!\n");
            free_png(&input_image);
            exit(40);
        }
    }
    /* проверка на корректность и количество введённых параметров пентаграммы в круге */
    if (pentagram.p) {
        if (check_pentagram(&pentagram))
            draw_pentagram(pentagram.center, pentagram.radius, pentagram.thickness, pentagram.color, &input_image);
        else {
            printf("You don't specify all parameters for pentagram!\n");
            free_png(&input_image);
            exit(40);
        }
    }
    /* запись файла */
    write_png_file(information.output_file, &input_image);
    return 0;
}
