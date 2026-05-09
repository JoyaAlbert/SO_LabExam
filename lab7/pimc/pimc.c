#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main( int argc, char *argv[])
{
  double piq, xdelta, ydelta;
  long i, niter, in, out;

  if( argc != 2)
  {
    printf("Invalid number of arguments. Usage:\n");
    printf("%s <iterations>\n", argv[0]);
    exit( -1);
  }

  niter = atol( argv[1]);

  in = out = 0;
  srand48( time( NULL));

  for( i = 0; i < niter; i++)
  {
    xdelta = drand48()-0.5;
    ydelta = drand48()-0.5;

    if( xdelta*xdelta + ydelta*ydelta <= 0.25) /* 0.25 is 0.5^2 */
      in++;
    else
      out++;
  }
  piq=(double)in/(double)(in + out);

  printf("Finished after %ld iterations.\n", niter);
  printf("Calculated value: %lf\n", 4*piq);

  return 0;
}

