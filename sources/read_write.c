#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include "../include/png_objects.h"
#include "../include/read_write.h"

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
        fclose(fp);
        exit(0);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr)
    {
        printf("Error in png info-structure (information is broken)!\n");
        png_destroy_read_struct(&image->png_ptr, NULL, NULL);
        fclose(fp);
        exit(0);
    }
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        printf("Unknown Error!\n");
        png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
        fclose(fp);
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
        fclose(fp);
        exit(0);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr)
    {
        printf("It\'s impossible to write the information of file \"%s\"!\n", file_name);
        png_destroy_write_struct(&image->png_ptr, NULL);
        fclose(fp);
        exit(0);
    }
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
        fclose(fp);
        exit(0);
    }

    png_init_io(image->png_ptr, fp);
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
        fclose(fp);
        exit(0);
    }
    png_write_image(image->png_ptr, image->row_pointers);
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
        fclose(fp);
        exit(0);
    }
    png_write_end(image->png_ptr, NULL);
    for (y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);
    fclose(fp);
}

void process_file(struct Png *image)
{
    int x, y;
    if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB)
    {
        // Some error handling: input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA
    }

    else if (png_get_color_type(image->png_ptr, image->info_ptr) != PNG_COLOR_TYPE_RGBA)
    {
        // Some error handling: color_type of input file must be PNG_COLOR_TYPE_RGBA
    }
    for (y = 0; y < image->height; y++)
    {
        png_byte *row = image->row_pointers[y];
        for (x = 0; x < image->width; x++)
        {
            png_byte *ptr = &(row[x * 4]);
            ptr[0] = ptr[3];
            ptr[1] = ptr[0];
            ptr[2] = ptr[1];
            ptr[3] = ptr[2];
        }
    }
}