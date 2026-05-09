#include <stdio.h>
#include <stdlib.h>
#include "integrate_mt.h"
#include "f.h"

int main( int argc, char * argv[]){
  int nthreads;
  long ndiv;
  double result;

  if( argc < 3){
    printf("Invalid arguments. Usage:\n");
    printf("%s <number of threads> <number of integral steps>\n", argv[0]);
    return -1;
  }

  nthreads = atoi( argv[1]);
  ndiv = atol( argv[2]);
  tr_integrate_mt( &result, 0.0, 1.0, ndiv, nthreads, f);
  printf("Valor calculado: %.14lf\n", 4.0 * result);

  return 0;
}
