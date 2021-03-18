#ifndef TO_PNG
#define TO_PNG

#include <stdint.h>

#include "generation.h"

typedef struct
{
	uint8_t red;
	uint8_t green;
        uint8_t blue;
}pixel_t;

typedef struct
{
        pixel_t *pixels;
	size_t width;
        size_t height;
}bitmap_t;

void to_png(matrix_t * m, int g, char *f);

#endif
