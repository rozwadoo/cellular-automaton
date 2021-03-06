#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Biblioteki używanie do stworzenia folderu
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "generation.h"

void to_pbm(matrix_t * m, int g, char *f)
{
	//Stworzenie folderu na grafiki
	if(g > 0) 
		mkdir("stworzone_pliki", 0777);
		
	int i;
	for(i = 0; i < g; i++)
	{
		char nazwa[100];
		strcpy(nazwa, f);
		char liczba[10];
		sprintf(liczba, "%d", i);
		strcat(nazwa, liczba);
		printf("%s\n", nazwa); 
	}
}

