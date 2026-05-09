#include <stdio.h>

int main( int argc, char* argv[])
{
	int i;
	int x = 0;

	for( i = 0; i < 10; i++)
	{
		x = x + i;
		printf("El valor de x es: %d\n", x);
	}

	printf("FIN DEL PROGRAMA.\n");
		
	return 0;
}
