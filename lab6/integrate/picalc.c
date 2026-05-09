#include <stdio.h>
#include <stdlib.h>
#include "integrate.h"
#include "f.h"

int main( int argc, char * argv[]){
  long ndiv;
  double result;

  if( argc < 2){
    printf("Invalid arguments. Usage:\n");
    printf("%s <number of integral steps>\n", argv[0]);
    return -1;
  }

  ndiv = atol( argv[1]);
  tr_integrate( &result, 0.0, 1.0, ndiv, f);
  printf("Valor calculado: %.14lf\n", 4.0 * result);

  return 0;
}
