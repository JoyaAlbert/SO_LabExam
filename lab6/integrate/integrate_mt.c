#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "integrate_mt.h"
#include "integrate.h"

void * tr_integrate_thread(void * arg);

int tr_integrate_mt( double * result, double x1, double x2, long nstep, int nthreads, double(*f)(double)){

  int i;
  pthread_t th[nthreads];
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  struct th_work w[nthreads];

  *result = 0.0;

  th_distribute_work( w, nthreads, x1, x2, nstep);

  for( i=0; i<nthreads; i++){
    w[i].f = f;
    w[i].presult = result;
    w[i].pmutex = &mutex;
    pthread_create( &th[i], NULL, tr_integrate_thread, &w[i]);
  }

  for(i=0; i<nthreads; i++)
    pthread_join( th[i], NULL);
      
  pthread_mutex_destroy( &mutex);
  return(0);
}

void * tr_integrate_thread(void * arg)
{
  double result;
  struct th_work * w = (struct th_work *)arg;
    
  tr_integrate( &result, w->x_start, w->x_end, w->n_steps, w->f);
    
  pthread_mutex_lock( w->pmutex);
  *(w->presult) += result;
  pthread_mutex_unlock( w->pmutex);

  pthread_exit( NULL);
}

void th_distribute_work( struct th_work * w, int n_th, double x_start, double x_end, unsigned long total_steps){

  int i;
  double stepsize = (x_end - x_start)/total_steps;

  for( i=0; i<n_th; i++)
  {
    w[i].x_start = x_start;
    w[i].n_steps = total_steps / ( n_th - i);
    w[i].x_end = x_start + w[i].n_steps * stepsize;
    total_steps -= w[i].n_steps;
    x_start = w[i].x_end;
  }
}
