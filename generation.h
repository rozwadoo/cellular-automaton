#ifndef GENERACJE_H
#define GENERACJE_H

#include <stdio.h>


typedef struct {
	int rn;
	int cn;
	int **e;
} matrix_t;

//Nowy kod tworzy jedną generacje
void iterate(matrix_t * m, int rs, int b);

//Alokuje dynamicznie tablie podaną w kodzie 
void start_matrix(matrix_t * m, FILE *in);

//Uzupełnia zerami i komurkami żywymi
void uzupelnij_matrix(matrix_t * m, FILE * in);

//Zwalnia pamięć
void free_matrix(matrix_t * m);

//Zapisuje do pliku
void zapis_koncowy(matrix_t * m, FILE *out);

#endif
