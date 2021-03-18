/*m[h][w]
0 - dead
1 - emerging
2 - alive
3 - vanishing */
#include <stdio.h>
#include <stdlib.h>
#include "generation.h"
#include "images.h"
#include <sys/stat.h>
#include <sys/types.h>


void iterate (matrix_t * m, int rs)
{
    int h = m->rn;
    int w = m->cn;
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w; ++j)	//pętla po wszystkich elementach macierzy
            {
                int s = 0;	//liczba żywych sąsiadów
		// pierwszy if sprawdza czy dany typ sąsiada powinien być sprawdzany w przypadku badanej komórki
		// drugi if sprawdza czy ten sąsiad jest żywy
                if(i != 0) if(m->e[i-1][j] > 1) s += 1;		//środkowy, górny sąsiad 
                if(j != 0) if(m->e[i][j-1] > 1) s += 1;		//lewy, środkowy sąsiad
                if(j!= w - 1) if(m->e[i][j+1] > 1) s += 1;		//prawy, środkowy sąsiad
                if(i != h - 1) if(m->e[i+1][j] > 1) s += 1;	//środkowy, dolny sąsiad
		if(rs == 0)
		{
			if(i != 0 && j!= 0) if(m->e[i-1][j-1] > 1) s += 1;		//lewy, górny sąsiad
                	if(i != 0 && j!= w - 1) if(m->e[i-1][j+1] > 1) s += 1;		//prawy, górny sąsiad
			 if(i != h - 1 && j!= 0) if(m->e[i+1][j-1] > 1) s += 1;		//lewy, dolny sąsiad
                	if(i != h - 1 && j!= w - 1) if(m->e[i+1][j+1] > 1) s += 1;	//prawy, dolny sąsiad
                }
		if(m->e[i][j] == 2) // jeśli badana komórka jest była żywa
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
			if( m->e[i][j] == 2)
				fprintf(out, "%d %d\n", i, j);
		}
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
	fscanf(in, "%d %d", &f, &s);
	m->e = malloc(sizeof(int *) * f );
	for(i = 0; i < f; i++)
	{
		m->e[i] = malloc(sizeof(int) * s);
	}
	if(m == NULL){
		printf("Błąd allokacji pamięci.");
		exit (EXIT_FAILURE);
	}
	m->rn = f;
	m->cn = s;
}

void uzupelnij_matrix(matrix_t * m, FILE *in)
{
	//Wypełnienie tablicy zerami
	int i, j, h, w;
	h = m->rn;
	w = m->cn;
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			m->e[i][j] = 0;
		}
	}	
	//Wprowazenie żywych kompurek
	while( fscanf(in, "%d %d", &i, &j) == 2)
	{
		m->e[i][j] = 2;
	}	

}


void free_matrix(matrix_t * m)
{
	free(m);
}



/*
int main( int argc, char **argv)
{
    int n = atoi(argv[1]);
    m = malloc(sizeof *m);
    if (m == NULL)
    return NULL;
  if ((m->e =
       malloc ((size_t) 5 * (size_t) 4 * sizeof *m->e)) == NULL) {
    free (m);
    return NULL;
  }
    m->rn = 5;
    m->cn = 4;
    int v[20] = { 2, 0, 0, 2, 0, 2, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0};
    for( int i = 0; i < 20; ++i)
    {
        m->e[i] = v[i];
    }
    for(int i = 0; i < m->rn; ++i)
        {
            printf("\n");
            for(int j = 0; j < m->cn; ++j)
            {
                printf("%d ", m->e[i*m->cn + j]);
            }
        }
    iterate(n);
    return 0;
}
*/
