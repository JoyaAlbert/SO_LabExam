#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

long i, in, out;

void mysigaction( int n, siginfo_t * info, void * context);



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
  printf("Process launched (PID=%d)\n", getpid());
  niter = atol( argv[1]);
  segsAlarm = atol( argv[2]);

  a.sa_sigaction = mysigaction;
  sigemptyset( &a.sa_mask);
  a.sa_flags = SA_SIGINFO;

  sigaction( SIGALRM, &a, NULL);
  sigaction(SIGINT, &a, NULL);
  sigaction(SIGUSR1, &a, NULL);
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

  printf("Finalizado después de %ld iteraciones \n", niter);
  printf("Valor calculado: %lf\n", 4*piq);

  return 0;
}
void mysigaction( int n, siginfo_t * info, void * context){
    double piq;

    piq = 0.0;
    if( in + out > 0)
      piq = (double)in/(double)(in + out);

    if(n == SIGALRM){
      printf("Finished by timeout after %ld iterations.\n", i);
      printf("Calculated value: %lf\n", 4*piq);
      exit(0);
    }
    if(n == SIGINT){
      printf("Finished by interruption.\n");
      printf("Calculated value: %lf\n", 4*piq);
      exit(0);
    }
    if(n == SIGUSR1){
      printf("Partial result requested (SIGUSR1 from %d).\n", info->si_pid);
      printf("Current calculated value: %lf\n", 4*piq);
    }
}  
