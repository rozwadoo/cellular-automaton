#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "generation.h"

char *usage = 
	"Użycie: -n liczba_generacji -g liczba_grafik -p plik_wejściowy -w plik_wyjściowy -f nazwa_grafik -s rodzaj sąsiedztwa (0- Moore'a, 1- von Neumanna)";

int main(int argc, char **argv)
{
	int n;
	int g;
	char *p;
	char *w;
	char *f;
	int s = 0;	//domyślnie rozważane jest sąsiedztwo Moore'a
	int opt;

	if(argc < 6)
	{
		printf("Za mało argumentów.\n");
		puts(usage);
		exit( EXIT_FAILURE );
	}

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
	
	FILE *p_wej = fopen(p, "r");
	if(p_wej == NULL)
	{
		printf("Nie mogę odczytać pliku wejściowego %s.\n", p);
		exit (EXIT_FAILURE);
	}
	start_matrix(p_wej, g);
	
	FILE *out = fopen(w, "w");
	iterate(n, out, g, f, s);

}
