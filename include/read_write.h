/**
 * \file read_write.h
 */
#ifndef READ_WRITE_C
#define READ_WRITE_C

/*!
 * \brief функция для чтения изображения PNG
 * \param file_name
 * \param image
 */
void read_png_file(char *file_name, Png *image);

/*!
 * \brief функция для записи изображения PNG
 * \param file_name
 * \param image
 */
void write_png_file(char *file_name, Png *image); /* функция для записи файла */

#endif
