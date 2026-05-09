#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

long i, in, out;

void mysigaction(int n)
{
  double piq;

  piq = 0.0;
  if( in + out > 0)
    piq = (double)in/(double)(in + out);

  printf("Finished by timeout after %ld iterations.\n", i);
  printf("Calculated value: %lf\n", 4*piq);
  exit(0);
}

int main( int argc, char *argv[])
{
  double piq, xdelta, ydelta;
  long niter;
  long segsAlarm;
  struct sigaction a;

  if( argc != 3)
  {
    printf("Invalid number of arguments. Usage:\n");
    printf("%s <iterations> <timeout>\n", argv[0]);
    exit( -1);
  }

  niter = atol( argv[1]);
  segsAlarm = atol( argv[2]);

  printf("Process launched (PID=%d)\n", getpid());

  a.sa_handler = mysigaction;
  sigemptyset( &a.sa_mask);
  a.sa_flags = 0;
  sigaction( SIGALRM, &a, NULL);
  alarm( segsAlarm);

  i = in = out = 0;
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

  printf("Finalizado despues de %ld iteraciones.\n", niter);

  printf("Valor calculado: %lf\n", 4*piq);

  return 0;
}
