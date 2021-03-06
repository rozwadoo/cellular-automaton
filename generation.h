#ifndef GENERACJE_H
#define GENERACJE_H

#include <stdio.h>


typedef struct {
	int rn;
	int cn;
	int *e;
} matrix_t;

void iterate(int n);

void start_matrix(FILE *in);

#endif
