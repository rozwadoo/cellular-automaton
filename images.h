#ifndef IMAGES_H
#define IMAGES_H

#include "generation.h"

void to_pbm(matrix_t * m, int g, char *f);

void stworz_folder();

void nazwa_pliku_pbm(char *nazwa, char *f, int numer);

void nazwa_pliku_png(char *nazwa, char *f, int numer);

#endif
