#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Biblioteki używanie do stworzenia folderu
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "generation.h"

//Przygotowanie do tworzenia plików
int numer=1;
int i;
char *przed = "Stworzone_pliki/";
char *kon = ".pbm";
char nazwa[100];
char nr[10];

void to_pbm(matrix_t * m, int g, char *f)
{
	//Tworzenie nazw plików
	strcpy(nazwa, "");
	strcpy(nazwa, przed);
	strcat(nazwa, f);
	sprintf(nr, "%i", numer++);
	strcat(nazwa, nr);
	strcat(nazwa, kon);
	
	//Tworzenie plików
	FILE *gra = fopen(nazwa, "w");
	fprintf(gra, "P1\n"); 	
	fprintf(gra, "#komentarz\n"); 	
	fprintf(gra, "%d %d\n", m->rn, m->cn); 		
	int i,j;
	for(i = 0; i < m->rn; i++)
	{
		for(j = 0; j < m->cn; j++)
		{
			if(m->e[i * m->cn + j] == 2)
				fprintf(gra, "%d ", 1);
			else
				fprintf(gra, "%d ", 0);
		}
		fprintf(gra, "\n");
	}	
	fclose(gra);
}

