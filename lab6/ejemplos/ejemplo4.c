#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TOTAL_COUNT 400000000

long x = 0;
pthread_mutex_t mutex;

void * thread_func( void * arg){

  long count = *(long *)arg;
  long local = 0;

  for( long i = 0; i < count; i++)
    local++;

  pthread_mutex_lock(&mutex);
  x += local;
  pthread_mutex_unlock(&mutex);

  return NULL;
}

int main( int argc, char* argv[]){

  long total_count = TOTAL_COUNT;
  int nthreads;

  if( argc == 1)
    nthreads = 1;
  else
    nthreads = atoi( argv[1]);

  pthread_t th[nthreads];
  long th_count[nthreads];

  pthread_mutex_init(&mutex, NULL);

  for( int i = 0; i < nthreads; i++){
    th_count[i] = total_count/(nthreads-i);
    pthread_create( &th[i], NULL, thread_func, &th_count[i]);
    total_count -= th_count[i];
  }
  for( int i = 0; i < nthreads; i++)
    pthread_join( th[i], NULL);


  pthread_mutex_destroy(&mutex);

  printf("%ld\n", x);

  return 0;
}



