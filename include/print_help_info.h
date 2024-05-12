#ifndef PRINT_HELP_INFO_H
#define PRINT_HELP_INFO_H

/**
 * \brief Функция, которая печатает информацию о изображении.
 * @param [in] input_file
 * @param [in] png
 * \details Принимает указатель на строку с именем файла и структуру с информацией об изображении.
 */
void print_info(char *input_file, Png *png);

/**
 * \brief Функция, которая печатает справку о программе.
 * \details Описывает, какие есть возможные аргументы (короткие и длинные флаги), в каком виде принимает аргумент.
 */
void print_help();

#endif