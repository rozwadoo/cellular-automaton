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
char *kon1 = ".pbm";
char *kon2 = ".png";
char nr[10];

void nazwa_pliku_pbm(char *nazwa, char *f, int numer)
{
	strcpy(nazwa, "");
	strcpy(nazwa, przed);
	strcat(nazwa, f);
	sprintf(nr, "%i", numer);
	strcat(nazwa, nr);
	strcat(nazwa, kon1);
}

void nazwa_pliku_png(char *nazwa, char *f, int numer)
{
	strcpy(nazwa, "");
	strcpy(nazwa, przed);
	strcat(nazwa, f);
	sprintf(nr, "%i", numer);
	strcat(nazwa, nr);
	strcat(nazwa, kon2);
}

void stworz_folder()
{
	mkdir("Stworzone_pliki", 0777 );
}
