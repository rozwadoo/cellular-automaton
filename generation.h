#ifndef GENERACJE_H
#define GENERACJE_H

#include <stdio.h>


typedef struct {
	int rn;
	int cn;
	int *e;
} matrix_t;

void iterate(int n, FILE *out, int g, char* f, int rs);

void start_matrix(FILE *in, int g);

void free_matrix();

#endif
