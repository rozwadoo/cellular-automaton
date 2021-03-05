/*m[h][w]
0 - dead
1 - emerging
2 - alive
3 - vanishing */
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int rn;
    int cn;
    int *e;
} matrix_t;
void iterate ( matrix_t * m, int n)
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
        for(int i = 0; i < h; ++i)
        {
            printf("\n");
            for(int j = 0; j < w; ++j)
            {
                printf("%d ", m->e[i*w + j]);
            }
        }
    }
}
int main( int argc, char **argv)
{
    int n = atoi(argv[1]);
    matrix_t *m = malloc (sizeof *m);
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
    iterate(m, n);
    return 0;
}
