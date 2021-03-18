#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ftw.h>

//Biblioteki używanie do stworzenia folderu
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "generation.h"

char *przed = "Stworzone_pliki/";
char *kon = ".pbm";
char nr[10];
char nazwa[100];

void nazwa_pliku(char *f, int numer);

void to_pbm(matrix_t * m, int g, char *f)
{
	nazwa_pliku(f, g);
	
	//Tworzenie plików
	FILE *gra = fopen(nazwa, "w");
	
	if(gra == NULL){
		printf("%s, nie mogę wczytać pliku", nazwa);
		exit (EXIT_FAILURE);
	}

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

void stworz_folder()
{
	mkdir("Stworzone_pliki", 0777 );
}

void nazwa_pliku(char *f, int numer)
{
	//Tworzenie nazw plików
	strcpy(nazwa, "");
	strcpy(nazwa, przed);
	strcat(nazwa, f);
	sprintf(nr, "%i", numer);
	strcat(nazwa, nr);
	strcat(nazwa, kon);
}

