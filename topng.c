#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </usr/local/include/png.h>
#include </usr/local/include/libpng15/png.h>
#include "topng.h"



pixel_t * pixel_at (bitmap_t * bitmap, int x, int y)
{
    return bitmap->pixels + bitmap->width * y + x;
}

int save_png_to_file (bitmap_t *bitmap, const char *path)
{
    FILE * fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    int x, y;
    png_byte ** row_pointers = NULL;
    int status = -1;
    int pixel_size = 3;
    int depth = 8;
    
    fp = fopen (path, "wb");
    if (! fp) {
        goto fopen_failed;
    }

    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        goto png_create_write_struct_failed;
    }
    
    info_ptr = png_create_info_struct (png_ptr);
    if (info_ptr == NULL) {
        goto png_create_info_struct_failed;
    }
    

    if (setjmp (png_jmpbuf (png_ptr))) {
        goto png_failure;
    }
    

    png_set_IHDR (png_ptr,
                  info_ptr,
                  bitmap->width,
                  bitmap->height,
                  depth,
                  PNG_COLOR_TYPE_RGB,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);
    

    row_pointers = png_malloc (png_ptr, bitmap->height * sizeof (png_byte *));
    for (y = 0; y < bitmap->height; ++y) {
        png_byte *row = 
            png_malloc (png_ptr, sizeof (int) * bitmap->width * pixel_size);
        row_pointers[y] = row;
        for (x = 0; x < bitmap->width; ++x) {
            pixel_t * pixel = pixel_at (bitmap, x, y);
            *row++ = pixel->red;
            *row++ = pixel->green;
            *row++ = pixel->blue;
        }
    }
    

    png_init_io (png_ptr, fp);
    png_set_rows (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);


    status = 0;
    
    for (y = 0; y < bitmap->height; y++) {
        png_free (png_ptr, row_pointers[y]);
    }
    png_free (png_ptr, row_pointers);
    
 png_failure:
 png_create_info_struct_failed:
    png_destroy_write_struct (&png_ptr, &info_ptr);
 png_create_write_struct_failed:
    fclose (fp);
 fopen_failed:
    return status;
}

int createImage(world_t * world, const char *path){
	
	bitmap_t obrazek;
	int x,y;
	obrazek.width = world->width;
	obrazek.height = world->height;
	
	obrazek.pixels = calloc (sizeof (pixel_t), obrazek.width * obrazek.height);
	for (y = 0; y < obrazek.height; y++) {
		for (x = 0; x < obrazek.width; x++) {
			if(world->array[y][x].on == 1){
				pixel_t * pixel = pixel_at (& obrazek, x, y);
				pixel->red = 0;
				pixel->green = 0;
				pixel->blue = 0;
			}else{
				pixel_t * pixel = pixel_at (& obrazek, x, y);
				pixel->red = 255;
				pixel->green = 255;
				pixel->blue = 255;
			}
			}
		}
	save_png_to_file (& obrazek, path);
	free(obrazek.pixels);
    return 0;

}
int createScaledImage(world_t * world, const char *path, int scale){
	
	bitmap_t obrazek;
	int x,y,i,j;
	obrazek.width = world->width * scale;
	obrazek.height = world->height * scale;
	
	obrazek.pixels = calloc (sizeof (pixel_t), obrazek.width * obrazek.height);
	for (y = 0; y < world->height; y++) {
		for (x = 0; x < world->width; x++) {
			if(world->array[y][x].on == 1){
				for(j = y * scale; j<y * scale + scale; j++){
					for(i = x * scale; i<x * scale + scale; i++){
					pixel_t * pixel = pixel_at (& obrazek, i, j);
					pixel->red = 0;
					pixel->green = 0;
					pixel->blue = 0;
					
					}
				
				}
			}else{
				for(j = y * scale; j<y * scale + scale; j++){
					for(i = x * scale; i<x * scale + scale; i++){
					pixel_t * pixel = pixel_at (& obrazek, i, j);
					pixel->red = 255;
					pixel->green = 255;
					pixel->blue = 255;
					
					}
				
				}
			}
			}
		}
	save_png_to_file (& obrazek, path);
	free(obrazek.pixels);
    return 0;

}