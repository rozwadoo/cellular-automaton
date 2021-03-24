#include <stdio.h>	
#include "generation.h"
	int VN(int i,int j,matrix_t * m)
	{
		int s = 0;
		int h = m->rn;
		int w = m->cn;
		//liczba żywych sąsiadów
		// pierwszy if sprawdza czy dany typ sąsiada powinien być sprawdzany w przypadku badanej komórki
		// drugi if sprawdza czy ten sąsiad jest żywy
		if(i != 0) if(m->e[i-1][j] > 1) s += 1;		//środkowy, górny sąsiad 
		if(j != 0) if(m->e[i][j-1] > 1) s += 1;		//lewy, środkowy sąsiad
		if(j != w - 1) if(m->e[i][j+1] > 1) s += 1;	//prawy, środkowy sąsiad
		if(i != h - 1) if(m->e[i+1][j] > 1) s += 1;	//środkowy, dolny sąsiad
		return s;
	}
		
	int Moore(int i,int j,matrix_t * m)
	{
		int s = VN(i, j, m);
		int h = m->rn;
		int w = m->cn;
		if(i != 0 && j!= 0) if(m->e[i-1][j-1] > 1) s += 1;		//lewy, górny sąsiad
        	if(i != 0 && j!= w - 1) if(m->e[i-1][j+1] > 1) s += 1;		//prawy, górny sąsiad
		if(i != h - 1 && j!= 0) if(m->e[i+1][j-1] > 1) s += 1;		//lewy, dolny sąsiad
        	if(i != h - 1 && j!= w - 1) if(m->e[i+1][j+1] > 1) s += 1;	//prawy, dolny sąsiad
   		return s;
	}
		
	int VN2(int i,int j,matrix_t * m)
	{
		int s = 0;
		int h = m->rn;
		int w = m->cn;
		if(i == 0) if(m->e[h-1][j] > 1) s += 1;		//środkowy, górny sąsiad 	
		if(j == 0) if(m->e[i][w-1] > 1) s += 1;		//lewy, środkowy sąsiad
		if(j == w - 1) if(m->e[i][0] > 1) s += 1;	//prawy, środkowy sąsiad
		if(i == h - 1) if(m->e[0][j] > 1) s += 1;	//środkowy, dolny sąsiad
		return s;
	}
	
	int Moore2(int i,int j,matrix_t * m)
	{
		int s = VN2(i, j, m);
		int h = m->rn;
		int w = m->cn;
		//narożniki
		if(i == 0 && j == 0) if(m->e[h-1][w-1] > 1) s += 1;		//lewy, górny sąsiad
        	if(i == 0 && j == w - 1) if(m->e[h-1][0] > 1) s += 1;		//prawy, górny sąsiad
		if(i == h - 1 && j == 0) if(m->e[0][w-1] > 1) s += 1;		//lewy, dolny sąsiad
        	if(i == h - 1 && j == w - 1) if(m->e[0][0] > 1) s += 1;		//prawy, dolny sąsiad
		//krawędzie
		if(i == 0 && j != 0) if(m->e[h-1][j-1] > 1) s += 1;		//lewy, górny sąsiad
		if(i != 0 && j == 0) if(m->e[i-1][w-1] > 1) s += 1;			
       		if(i == 0 && j != w - 1) if(m->e[h-1][j+1] > 1) s += 1;		//prawy, górny sąsiad
		if(i != 0 && j == w - 1) if(m->e[i-1][0] > 1) s += 1;		
		if(i != h - 1 && j == 0) if(m->e[i-1][w-1] > 1) s += 1;		//lewy, dolny sąsiad
		if(i == h - 1 && j != 0) if(m->e[0][j-1] > 1) s += 1;		
        	if(i == h - 1 && j != w - 1) if(m->e[0][j+1] > 1) s += 1;	//prawy, dolny sąsiad
		if(i != h - 1 && j == w - 1) if(m->e[i-1][0] > 1) s += 1;		
    		return s;
	}





int licz_boki(int i, int j, int h, int w, int rs)
{
	int a = rs + 2;
	if(i == 0 && j == 0)return a;
	else
	if(i == h-1 && j == w-1)return a;
	else
	if(i == 0 && j == w-1)return a;
	else
	if(i == h-1 && j == 0)return a;
	else
	if(i == 0 || j == 0 || i == h-1 || j == w-1)return 1;
	else return 0;
}

