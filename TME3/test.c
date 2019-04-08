#include <stdlib.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
	int tab[10][10];


	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
	printf("%d\n",tab[i][j] );
		}
	}
	return 0;
}