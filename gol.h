#ifndef GOL_H
#define GOL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </usr/local/include/png.h>
#include </usr/local/include/libpng15/png.h>
#include "struct.h"

void printworld(world_t *world, FILE *pOutput);

void randomizeworld(world_t *world);
 
void updateworld(world_t *world);
 
void destroyworld(world_t *world);
 
int createworld(world_t *world, int width, int height);

#endif