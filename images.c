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
char *kon = ".pbm";
char nazwa[100];
char nr[10];

void to_pbm(matrix_t * m, int g, char *f)
{
	//Tworzenie nazw plików
	strcpy(nazwa, "");
	strcat(nazwa, f);
	sprintf(nr, "%i", numer++);
	strcat(nazwa, nr);
	strcat(nazwa, kon);
	printf("%s\n", nazwa);
	
	//Tworzenie plików
		
}

