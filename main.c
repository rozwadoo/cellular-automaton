#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "generation.h"

char *usage = 
	"Użycie:\n"
	"   -n liczba_generacji (domyślnie 100)\n" 
	"   -g liczba_grafik (domyślnie 100)\n"
	"   -p plik_wejściowy (domyślnie test/pistolet)\n"
	"   -w plik_wyjściowy (domyślnie ostatnia_generacja.txt)\n" 
	"   -f nazwa_grafik (domyślnie grafika)\n"
	"   -s rodzaj sąsiedztwa (0- Moore'a, 1- von Neumanna)(domyślnie 0)";

int main(int argc, char **argv)
{
	int n;
	int g;
	char *p;
	char *w;
	char *f;
	int s = 0;	//domyślnie rozważane jest sąsiedztwo Moore'a
	int opt;

	while((opt = getopt (argc, argv, "n:g:p:w:f:s:")) != -1)
	{
		switch (opt)
		{
			case 'n':
				n = atoi(optarg);
				break;
		
			case 'g':
				g = atoi(optarg);
				break;
		
			case 'p':
				p = optarg;
				break;
			
			case 'w':
				w = optarg;
				break;
			
			case 'f':
				f = optarg;
				break;
			case 's':
				s = atoi(optarg);
				break;
		}
	}
	
	//Nadawanie wartości domyślnych
	if(n == 0){
		n = 100;
	}

	if(g == 0){
		n = 100;
	}
	
	if(p == NULL){
		p = "test";
	}
	
	if(w == NULL){
		w = "ostatniageneracja.txt";
	}
	
	if(f == NULL){
		f= "";
	}
	
	FILE *p_wej = fopen(p, "r");
	if(p_wej == NULL)
	{
		printf("Nie mogę odczytać pliku wejściowego %s.\n", p);
		exit (EXIT_FAILURE);
	}
	
	matrix_t * m = NULL;

	start_matrix(m, p_wej, g);
	
	FILE *out = fopen(w, "w");
	if(out == NULL)
	{
		printf("Nie mogę odczytać pliku wyjściowego %s.\n", w);
		exit (EXIT_FAILURE);
	}
	
	iterate(m, n, out, g, f, s);
	
	free_matrix(m);
}
