#include <pthread.h>

struct th_work {
  double x_start;
  double x_end;
  long n_steps;
  double(*f)(double);
  double * presult;
  pthread_mutex_t * pmutex;
};

int tr_integrate_mt( double * result, double x1, double x2, long nstep, int nthreads, double(*f)(double));
void th_distribute_work( struct th_work * w, int n_th, double x_start, double x_end, unsigned long total_steps);
