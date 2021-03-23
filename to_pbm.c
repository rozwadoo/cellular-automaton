#include <stdio.h>
#include <stdlib.h>

#include "images.h"
#include "generation.h"


void to_pbm(matrix_t * m, int g, char *f)
{
	//Tworzenie nazwy
	char nazwa[100];
	nazwa_pliku_pbm(nazwa, f, g);
	
	//Otwarcie pliku
	FILE *gra = fopen(nazwa, "w");		
	if(gra == NULL){
		printf("%s, nie mogę wczytać pliku", nazwa);
		exit (EXIT_FAILURE);
	}	
	
	//Wczytywanie do pliku
	fprintf(gra, "P1\n"); 	
	fprintf(gra, "#komentarz\n"); 	
	fprintf(gra, "%d %d\n", m->rn, m->cn); 		
	int i,j;
	for(i = 0; i < m->rn; i++)
	{
		for(j = 0; j < m->cn; j++)
		{
			if(m->e[i][j] == 2)
				fprintf(gra, "%d ", 1);
			else
				fprintf(gra, "%d ", 0);
		}
		fprintf(gra, "\n");
	}	
			
	fclose(gra);
}
