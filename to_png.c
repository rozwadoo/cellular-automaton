#include <png.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "to_png.h"
#include "images.h"
#include "generation.h"

void save_png_to_file (matrix_t * m, const char *path, int qq)
{
    png_structp png_ptr = NULL;
    
    png_infop info_ptr = NULL;
    
    png_bytep *row_pointers = NULL;
    
    png_byte color_type;
    png_byte bit_depth;
    
    color_type = PNG_COLOR_TYPE_GRAY;

    int i, j, x, y;

    int height = m->rn * 8;
    int width = m->cn * 8;
    int depth = 8;
    
    
    	row_pointers = (png_bytep*) malloc(sizeof(png_bytep)*height);
	for(i = 0; i < height; i++)
		row_pointers[i] = (png_byte*) malloc(sizeof(png_byte) * width);

	for(i = 0; i < height; i += 8)
	{
		for(j = 0; j < width; j += 8)
		{
			if(m->e[i/8][j/8] == 2)
			{
				for(x = 0; x < 8; x++)
				{
					for(y = 0; y < 8; y++)
					{
						row_pointers[i + y][j + x] = 255;
					}
				}
			}
			else
			{
				for(x = 0; x < 8; x++)
				{
					for(y = 0; y < 8; y++)
					{
						row_pointers[i + y][j + x] = 0;
					}
				}

			}
		}
	}



    FILE *fp = fopen (path, "wb");
    if (! fp) {
    	printf("ra");
    }

    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    
    if (png_ptr == NULL) {
        goto png_create_write_struct_failed;
    }

    info_ptr = png_create_info_struct (png_ptr);
    if (info_ptr == NULL) {
        goto png_create_info_struct_failed;
    }

    png_init_io (png_ptr, fp);
    
    if (setjmp (png_jmpbuf (png_ptr))) {
        goto png_failure;
    }

	    png_set_IHDR (png_ptr,
                  info_ptr,
                  width,
                  height,
                  depth,
                  color_type,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_BASE,
                  PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);
	
	png_write_image(png_ptr, row_pointers);
	
	png_write_end(png_ptr, NULL);

	png_destroy_write_struct(&png_ptr, &info_ptr);

    for (y = 0; y < height; y++) {
        png_free (png_ptr, row_pointers[y]);
    }
    png_free (png_ptr, row_pointers);

 png_failure:
 png_create_info_struct_failed:
    png_destroy_write_struct (&png_ptr, &info_ptr);
 png_create_write_struct_failed:
    fclose (fp);

}

void to_png(matrix_t * m, int g, char *f)
{
    int qq = 8;
    int q1,q2;   
    char nazwa[100];
    nazwa_pliku_png(nazwa, f, g);
    save_png_to_file (m, nazwa, qq ) ;
}
