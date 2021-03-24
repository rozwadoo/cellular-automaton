/*m[h][w]
0 - dead
1 - emerging
2 - alive
3 - vanishing */
#include <stdio.h>
#include <stdlib.h>
#include "generation.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "zasady_gry.h"

void iterate (matrix_t * m, int rs, int b)
{
    	int h = m->rn;
    	int w = m->cn;
	//wybór używanych funkcji w zależności od rodzaju sąsiedztwa	
	int (*fun)(int, int, matrix_t *);
	if(rs == 1) fun = VN;
	if(rs == 0) fun = Moore;
	int (*fun2)(int, int, matrix_t *);
	if(rs == 1) fun2 = VN2;
	if(rs == 0) fun2 = Moore2;
    	for(int i = 0; i < h; ++i)
    	{
        	for(int j = 0; j < w; ++j)	//pętla po wszystkich elementach macierzy
        	{
            		int s = fun(i, j, m);	//właściwe liczenie liczby żywych sąsiadów
			if(b == 1) s += licz_boki(i, j, h, w, rs);	//ewentualne dodanie żywych krawędzi
			if(b == 2) s += fun2(i, j, m);			//macierz działająca "na około"		

			if(m->e[i][j] == 2) // jeśli badana komórka była żywa
			{
                		if(s == 2 || s == 3) m->e[i][j] = 2;
                		else m->e[i][j] = 3;
            		}
            		else // jeśli badana komórka była martwa
            		{
                		if(s == 3) m->e[i][j] = 1;
                		else m->e[i][j] = 0;
            		}
        	}   
    	}
       

	for(int i = 0; i < h; ++i)	//update macierzy - zastępowanie komórek umierających martwymi, a rodzących się żywymi
        {
            for(int j = 0; j < w; ++j)
            {
                if(m->e[i][j] == 0 || m->e[i][j] == 3) m->e[i][j] = 0;
                else m->e[i][j] = 2;
            }
	}
}

void zapis_koncowy(matrix_t * m, FILE *out)
{
	fprintf(out, "%d %d\n", m->rn, m->cn);
	int i,j;
	for(i = 0; i < m->rn; i++)
	{
		for(j = 0; j < m->cn; j++)
		{
			if(m->e[i][j] == 2)
				fprintf(out, "%d ", 1);
			else
				fprintf(out, "%d ", m->e[i][j]);	
		}
		fprintf(out, "\n");
	}
}	 

void wypisz_matrix(matrix_t *m)
{
	int h = m->rn;
	int w = m->cn;
	for(int i = 0; i < h; ++i)
	{
            printf("\n");
            for(int j = 0; j < w; ++j)
            {
                printf("%d ", m->e[i][j]);
            }
        }
	printf("\n");
}


void start_matrix(matrix_t * m, FILE *in)
{
	//Zmienne pomocnicze
	int f;
	int s;
	int i;
	int j;
	
	//Alokacja pamięci dla tablicy
	fscanf(in, "%d %d", &(f), &(s));
	m->e = malloc(sizeof(int *) * f );
	m->rn = f;
	m->cn = s;
	for(i = 0; i < f; i++)
	{
		m->e[i] = malloc(sizeof(int) * s);
	}

	if(m == NULL)
	{
		printf("Błąd allokacji pamięci.");
		exit (EXIT_FAILURE);
	}
}

void uzupelnij_matrix(matrix_t * m, FILE *in)
{
	int i, j = 0;
	int w = m->cn;
	while( fscanf(in, "%d", &i) == 1)
	{
		if(i == 1) m->e[j/w][j%w] = 2;
		else
			m->e[j/w][j%w] = 0;
		
		j++;
	}	
}


void free_matrix(matrix_t * m)
{
	free(m);
}
