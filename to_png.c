#include <png.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "to_png.h"
#include "images.h"
#include "generation.h"

static pixel_t * pixel_at (bitmap_t * bitmap, int x, int y)
{
    return bitmap->pixels + bitmap->width * y + x;
}

static int save_png_to_file (bitmap_t *bitmap, const char *path)
{
    FILE * fp;      
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x,y;
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
    for (y = 0; y < bitmap->height; y++) {
        png_byte *row =
            png_malloc (png_ptr, sizeof (uint8_t) * bitmap->width * pixel_size);
        row_pointers[y] = row;
        for (x = 0; x < bitmap->width; x++) {
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

void to_png(matrix_t * m, int g, char *f)
{
    bitmap_t image;
    int status;
    int x = m->rn;//h
    int y = m->cn;//w

    status = 0;

        int qq = 32;
        image.width = y*qq;
        image.height = x*qq;

    image.pixels = calloc (image.width * image.height, sizeof (pixel_t));
    /* Write the image to a file 'fruit.png'. */
    int q1,q2;   
    for(q1 = 0; q1 < x; q1++)
	{
		for(q2 = 0; q2 < y; q2++)
		{
			if(m->e[q1][q2] == 2)
        		{
				int i,j;
                		for(i = 0; i < qq; i++)
                		{
                        		for(j = 0; j < qq; j++)
                       			{
   	               				pixel_t * pixel = pixel_at (&image, q1*qq+i, q2*qq+j);
        	                        	pixel->red = (int)255;
        	                       		pixel->green = (int)255;
        	                       		pixel->blue = (int)255;
        	       			}
        		        }
        		}
		}
	}
	char nazwa[100];
	nazwa_pliku_png(nazwa, f, g);

    if (save_png_to_file (&image, nazwa )) {
        fprintf (stderr, "Error writing file.\n");
        status = -1;
    }

    free (image.pixels);
}
