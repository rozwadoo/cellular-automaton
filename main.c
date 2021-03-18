#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "generation.h"
#include "images.h"

void help();

int main(int argc, char **argv)
{
	int n;
	int g;
	char *p = NULL;
	char *w = NULL;
	char *f = NULL;
	int s = 0;	//domyślnie rozważane jest sąsiedztwo Moore'a
	int opt;
	
	if(argc < 5){
		help();
		return 1;
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
		help();
		exit (EXIT_FAILURE);
	}
	
	matrix_t * m = malloc(sizeof *m);

	start_matrix(m, p_wej);

	uzupelnij_matrix(m, p_wej);
	
	stworz_folder();

	FILE *out = fopen(w, "w");
	if(out == NULL)
	{
		printf("Nie mogę odczytać pliku wyjściowego %s.\n", w);
		help();
		exit (EXIT_FAILURE);
	}
	
	int i;
	for(i = 0; i < n; i++)
	{
		iterate(m, s);
		if(i == n-1)zapis_koncowy(m, out);
		if(i < g)to_pbm(m, i+1, f);
	}

	free_matrix(m);
}



void help(){
	printf("Użycie: ./ca\n");
	printf("   -n liczba_generacji\n"); 
	printf("   -g liczba_grafik \n");
	printf("   -p plik_wejściowy \n");
	printf("   -w plik_wyjściowy \n");
	printf("   -f nazwa_grafik \n");
	printf("   -s rodzaj sąsiedztwa (0- Moore'a, 1- von Neumanna)(domyślnie 0)\n");
}
