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

matrix_t *m;

void iterate (int n, FILE *out, int g, char *f, int rs)
{
    int h = m->rn;
    int w = m->cn;
    for(int l = 0; l < n; ++l)	//pętla po wszystich iteracjach
    {
        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)	//pętla po wszystkich elementach macierzy
            {
                int s = 0;	//liczba żywych sąsiadów
		// pierwszy if sprawdza czy dany typ sąsiada powinien być sprawdzany w przypadku badanej komórki
		// drugi if sprawdza czy ten sąsiad jest żywy
                if(i != 0) if(m->e[i*w + j - w] > 1) s += 1;		//środkowy, górny sąsiad 
                if(j != 0) if(m->e[i*w + j - 1] > 1) s += 1;		//lewy, środkowy sąsiad
                if(j!= w - 1) if(m->e[i*w + j + 1] > 1) s += 1;		//prawy, środkowy sąsiad
                if(i != h - 1) if(m->e[i*w + j + w] > 1) s += 1;	//środkowy, górny sąsiad
		if(rs == 0)
		{
			if(i != 0 && j!= 0) if(m->e[i*w + j - w - 1] > 1) s += 1;		//lewy, górny sąsiad
                	if(i != 0 && j!= w - 1) if(m->e[i*w + j - w + 1] > 1) s += 1;		//prawy, górny sąsiad
			 if(i != h - 1 && j!= 0) if(m->e[i*w + j + w - 1] > 1) s += 1;		//lewy, dolny sąsiad
                	if(i != h - 1 && j!= w - 1) if(m->e[i*w + j + w + 1] > 1) s += 1;	//prawy, dolny sąsiad
                }
		if(m->e[i*w + j] == 2) // jeśli badana komórka jest była żywa
		{
                    if(s == 2 || s == 3) m->e[i*w + j] = 2;
                    else m->e[i*w + j] = 3;
                }
                else // jeśli badana komórka była martwa
                {
                    if(s == 3) m->e[i*w + j] = 1;
                    else m->e[i*w + j] = 0;
                }
            }   
        }
        for(int i = 0; i < h; ++i)	//update macierzy - zastępowanie komórek umierających martwymi, a rodzących się żywymi
        {
            for(int j = 0; j < w; ++j)
            {
                if(m->e[i*w + j] == 0 || m->e[i*w + j] == 3) m->e[i*w + j] = 0;
                else m->e[i*w + j] = 2;
            }
        }
	
	//DODANE
	if(l == n-1)
	{
		fprintf(out, "%d %d\n", m->rn, m->cn);
		int i,j;
		for(i = 0; i < m->rn; i++)
		{
			for(j = 0; j < m->cn; j++)
			{
				if( m->e[i * m->cn + j] == 2)
				{
					fprintf(out, "%d %d\n", i, j);
				}
			}
		}
	}
	to_pbm(m, g, f);

	//Wypisywanie testowe
        /*
	for(int i = 0; i < h; ++i)
        {
            printf("\n");
            for(int j = 0; j < w; ++j)
            {
                printf("%d ", m->e[i*w + j]);
            }
        }
	printf("\n");
	*/

    }
}


void start_matrix(FILE *in, int g)
{
	//Zmienne pomocnicze
	int f;
	int s;

	//Alokacja pamięci dla tablicy
	m = malloc(sizeof *m);
	fscanf(in, "%d %d", &f, &s);
	m->e = malloc(sizeof(int) * f * s);
	if(m == NULL){
		printf("Błąd allokacji pamięci.");
		exit (EXIT_FAILURE);
	}
	m->rn = f;
	m->cn = s;

	//Wypełnienie tablicy zerami
	int i;
	int j;
	for(i = 0; i < m->rn; i++)
	{
		for(j = 0; j < m->cn; j++)
		{
			m->e[i * m->cn + j] = 0;
		}
	}
	
	//Stworzenie folderu
	if(g > 0)mkdir("Stworzone_pliki", 0777);
		
	//Wprowazenie żywych kompurek
	while( fscanf(in, "%d %d", &f, &s) == 2)
	{
		m->e[f * m->cn + s] = 2;
	}	

}


void free_matrix()
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
