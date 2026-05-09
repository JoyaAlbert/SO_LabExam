#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "picalc_pipes.h"
#include "integrate.h"
#include "f.h"

void dispatcher( int workfd, int nwp, long total_steps){

  struct work w;
  double x_start = 0, x_end = 1;
  double stepsize = (x_end - x_start) / total_steps;

  for( int i = 0; i < nwp; i++){
    w.x_start = x_start;
    w.n_steps = total_steps / ( nwp - i); 
    w.x_end = x_start + w.n_steps * stepsize;
    total_steps -= w.n_steps;
    x_start = w.x_end;

    write( workfd, &w, sizeof( struct work)); 
  }
}

void gatherer( int resultfd){

  double result = 0, partialres;

  while( read( resultfd, &partialres, sizeof( double)) > 0)
    result+=partialres;

  result*=4;
  printf("Calculated value: %.14lf\n", result);
}

void worker( int workfd, int resultfd){

  struct work w;
  double acc;

  while( read( workfd, &w, sizeof( struct work)) > 0){ 
    tr_integrate( &acc, w.x_start, w.x_end, w.n_steps, f); 
    write( resultfd, &acc, sizeof( double));
  }
}

