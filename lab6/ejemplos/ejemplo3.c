#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TOTAL_COUNT 400000000

long x = 0;

pthread_mutex_t mutex;

void * thread_func( void * arg){

  long count = *(long *)arg;

  for( long i = 0; i < count; i++)
  {
    pthread_mutex_lock(&mutex);
    x++;
    pthread_mutex_unlock(&mutex);
  }

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

/* con mutex
# lab6/ejemplos on main ?:1 with changes 
> time ./ejemplo3 2
400000000

real	0m8,210s
user	0m11,310s
sys	0m4,985s
# lab6/ejemplos on main ?:1 with changes 
> time ./ejemplo3 56
400000000

real	0m15,297s
user	0m50,411s
sys	3m6,302s
# lab6/ejemplos on main ?:1 with changes 
> time ./ejemplo3 1
400000000

real	0m2,714s
user	0m2,702s
sys	0m0,002s
# lab6/ejemplos on main ?:1 with changes 
> time ./ejemplo3 99
400000000

real	0m15,386s
user	0m50,556s
sys	3m7,714s*/


/* No Mutex
# lab6/ejemplos on main ?:1 with changes 
> time ./ejemplo3 2
201142654

real	0m3,585s
user	0m7,132s
sys	0m0,001s
# lab6/ejemplos on main ?:1 with changes 
> time ./ejemplo3 1
400000000

real	0m0,294s
user	0m0,292s
sys	0m0,002s
# lab6/ejemplos on main ?:1 with changes 
> time ./ejemplo3 56
15867185

real	0m3,979s
user	1m1,544s
sys	0m0,006s
# lab6/ejemplos on main ?:1 with changes 
> time ./ejemplo3 99
10593494

real	0m3,976s
user	1m1,645s
sys	0m0,017s
*/

