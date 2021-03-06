#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "generation.h"

char *usage = 
	"Użycie: -n liczba_generacji -g liczba_grafik -p plik_wejściowy -w plik_wyjściowy -f nazwa_grafik";

int main(int argc, char **argv)
{
	int n;
	int g;
	char *p;
	char *w;
	char *f;
	int opt;

	if(argc < 5)
	{
		printf("Za mało argumentów.\n");
		puts(usage);
		exit( EXIT_FAILURE );
	}

	while((opt = getopt (argc, argv, "n:g:p:w:f")) != -1)
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
		}
	}
	
	FILE *p_wej = fopen(p, "r");
	
	if(p_wej == NULL)
	{
		printf("Nie mogę odczytać pliku wejściowego %s.\n", p);
		exit (EXIT_FAILURE);
	}
	
	start_matrix(p_wej);
	iterate(n);

}
