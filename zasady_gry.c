#include <stdio.h>

int licz_boki(int i, int j, int h, int w)
{
	if(i == 0 && j == 0)return 3;
	else
	if(i == h-1 && j == w-1)return 3;
	else
	if(i == 0 && j == w-1)return 3;
	else
	if(i == h-1 && j == 0)return 3;
	else
	if(i == 0 || j == 0 || i == h-1 || j == w-1)return 1;

}
