#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "generation.h"
#include "images.h"
#include "to_png.h"
#include "to_pbm.h"

void help();

int main(int argc, char **argv)
{
	int n;
	int g = 0;
	char *p = NULL;
	char *w = NULL;
	char *f = "";
	int s = 0;	//domyślnie rozważane jest sąsiedztwo Moore'a
	int opt;
	int o = 0;
	int b = 0;
	
	while((opt = getopt (argc, argv, "n:g:p:w:f:s:o:b:")) != -1)
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
		
			case 'o':
				o = atoi(optarg);
				break;

			case 'b':
			        b = atoi(optarg);	
				break;
		}
	}

	if( n == 0){
		printf("Nie podano ilości generacji.");
		help();
		exit (EXIT_FAILURE);
	}
	if( g == 0)g = n;
	
	if(p == NULL){
		printf("Nie podano pliku wejściowego.");
		help();
		exit (EXIT_FAILURE);
	}

	//Wczytanie pliku dancyh	
	FILE *p_wej = fopen(p, "r");
	if(p_wej == NULL)
	{
		printf("Nie mogę odczytać pliku wejściowego %s.\n", p);
		help();
		exit (EXIT_FAILURE);
	}

	//Alokowanie pamięci
	matrix_t * m = malloc(sizeof *m);
	start_matrix(m, p_wej);
	
	//Uzupełnianie o żywe komurki
	uzupelnij_matrix(m, p_wej);

	//Tworzenie folderu
	stworz_folder();

	//Grafika pliku wejściowego
	if(g>0){
		if(o == 0)to_png(m, 0, f);
		if(o == 1)to_pbm(m, 0, f);
	}

	//Wczytanie pliku do zapisu końcowego
	FILE *out = fopen(w, "w");
	if(out == NULL)
	{
		printf("Nie mogę odczytać pliku wyjściowego %s.\n", w);
		help();
		exit (EXIT_FAILURE);
	}
	
	//Kolejnie iteracje + tworzenie grafik pbm/png + zapis końcowy
	int i;
	for(i = 0; i < n; i++)
	{
		iterate(m, s, b);
		if(i == n-1)zapis_koncowy(m, out);
		if(o == 0)
		{
			if(i < g)to_png(m, i+1, f);
		}
		else
			if(i < g)to_pbm(m, i+1, f);
		
	}

	//Zwalnianie pamięci
	free_matrix(m);

}



void help(){
	printf("Użycie: ./ca\n");
	printf("   -n liczba_generacji (wymagane)\n"); 
	printf("   -p plik_wejściowy (wymagane) \n");
	printf("   -w plik_wyjściowy (wymagane)\n");
	printf("   -g liczba_grafik (w przypadku nie podania przyjmuje wartość n\n");
	printf("   -f nazwa_grafik \n");
	printf("   -s rodzaj sąsiedztwa (0- Moore'a, 1- von Neumanna)(domyślnie 0)\n");
	printf("   -o typ tworzonych plików (0- PNG, 1- PBM)(domyślnie 0)\n");
	printf("   -b zmienia zasady gry (0- boki są komurkami martwymi, 1- boki są komurkami żywymi, 2- pierwszy wiersz jest dolną krawędzią ostatniego wiersza, pierwsza kolumna jest prawą krawędzią ostatniej kolumny i na odwrót)(domyślnie 0)\n");
}
