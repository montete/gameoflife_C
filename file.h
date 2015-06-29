#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </usr/local/include/png.h>
#include </usr/local/include/libpng15/png.h>
#include "struct.h"

int gethg(char * plik);

int getwid (char * plik);

int getWymiar (char * plik, char * tryb);

int definedworld(char * plik, world_t *world);

int writeGame(world_t * world, char * filename);

#endif