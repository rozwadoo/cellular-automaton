/*m[h][w]
0 - dead
1 - emerging
2 - alive
3 - vanishing */
#include <stdio.h>
#include <stdlib.h>
#include "generation.h"
#include "images.h"

matrix_t *m;

void iterate (int n, FILE *out, int g, char *f)
{
    int h = m->rn;
    int w = m->cn;
    for(int l = 0; l < n; ++l)
    {
        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                int s = 0;
                if(i != 0 && j!= 0) if(m->e[i*w + j - w - 1] > 1) s += 1;
                if(i != 0) if(m->e[i*w + j - w] > 1) s += 1;
                if(i != 0 && j!= w - 1) if(m->e[i*w + j - w + 1] > 1) s += 1;
                if(j != 0) if(m->e[i*w + j - 1] > 1) s += 1;
                if(j!= w - 1) if(m->e[i*w + j + 1] > 1) s += 1;
                if(i != h - 1 && j!= 0) if(m->e[i*w + j + w - 1] > 1) s += 1;
                if(i != h - 1) if(m->e[i*w + j + w] > 1) s += 1;
                if(i != h - 1 && j!= w - 1) if(m->e[i*w + j + w + 1] > 1) s += 1;
                if(m->e[i*w + j] == 2) 
                {
                    if(s == 2 || s == 3) m->e[i*w + j] = 2;
                    else m->e[i*w + j] = 3;
                }
                else 
                {
                    if(s == 3) m->e[i*w + j] = 1;
                    else m->e[i*w + j] = 0;
                }
            }   
        }
        for(int i = 0; i < h; ++i)
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


void start_matrix(FILE *in)
{
	//Zmienne pomocnicze
	int f;
	int s;

	//Wczytanie pliku i allokacja pamięcie
	//FILE *in = fopen(plik, "r");
	m = malloc(sizeof *m);
	
	//Alokacja pamięci dla tablicy
	fscanf(in, "%d %d", &f, &s);
	m->e = malloc(sizeof(int) * f * s);
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
	
	//Wprowazenie żywych kompurek
	while( fscanf(in, "%d %d", &f, &s) == 2)
	{
		m->e[f * m->cn + s] = 2;
	}	

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
