#include <stdio.h>
#include <stdlib.h>

int main( int argc, char* argv[])
{
        int f0=0, f1=1, fn, fn_1, nterms, i;

        if( argc != 2)
        {
                printf("Error: Número de argumentos inválido.\n");
                printf("Sintaxis: %s num_terminos\n\n", argv[0]);
                exit(-1);
        }

        nterms = atoi( argv[1]);

        printf("%d", f0);

        fn_1 = f0;
        fn = f1;
        i = 2;

        while( i <= nterms)
        {
                int fnext;
                printf(", %d", fn);
                fnext = fn + fn_1;
                fn_1 = fn;
                fn = fnext;
                i++;
        }
        printf("\n");
}

