#ifndef TOPNG_H
#define TOPNG_H
#include <stdlib.h>
#include <string.h>
#include </usr/local/include/png.h>
#include </usr/local/include/libpng15/png.h>
#include "struct.h"



pixel_t * pixel_at (bitmap_t * bitmap, int x, int y);

int save_png_to_file (bitmap_t *bitmap, const char *path);

int createImage(world_t * world, const char *path);
int createScaledImage(world_t * world, const char *path, int scale);
#endif