#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integrate.h"

double my_f( double x){
  return fabs(x) <= 1 ? sqrt(1.0 - x * x) : 0.0;
}

int main( int argc, char* argv[]){

  long ndiv;
  double x1, x2, result;

  if( argc < 4)
  {
    printf("Invalid arguments. Usage:\n");
    printf("%s <x start> <x end> <number of integral steps>\n", argv[0]);
    exit( -1);
  }

  x1 = atof(argv[1]);
  x2 = atof(argv[2]);
  ndiv = atol(argv[3]);

  tr_integrate( &result, x1, x2, ndiv, exp);
  
  printf("Calculated value: %.14lf\n", result);

  return(0);
}
