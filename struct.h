
#ifndef STRUCT_H
#define STRUCT_H

typedef struct cell_t_ {
    struct cell_t_ *neighbours[8];
    int on;
} cell_t;
 
typedef struct world_t_ {
    cell_t **array;
    int width;
    int height;
    void *mem;
} world_t;

typedef struct pixel_t_ {
    int red;
    int green;
    int blue;
} pixel_t;
    
typedef struct bitmap_t_ {
    pixel_t *pixels;
    int width;
    int height;
} bitmap_t;

#endif