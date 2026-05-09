#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct thread_data {
  int nrep;
  char msg[10];
};

void * thread_func( void * arg){

  struct thread_data * data = (struct thread_data *)arg;
  int i = 0;

  while( i < data->nrep){
    usleep( rand() % 3000000);
    printf("(%02d) %s\n", i, data->msg);
    i++;
  }
  pthread_exit( NULL);
}

int main( int argc, char* argv[]){

  pthread_t th1, th2, th3;
  struct thread_data data1, data2, data3;

  data1.nrep = 5;
  strcpy(data1.msg, "Hello!");
  data2.nrep = 3;
  strcpy(data2.msg, "Hola!");
  data3.nrep = 4;
  strcpy(data3.msg, "Namaste!");

  pthread_create( &th1, NULL, thread_func, &data1);
  pthread_create( &th2, NULL, thread_func, &data2);
  pthread_create( &th3, NULL, thread_func, &data3);

  pthread_join( th1, NULL);
  pthread_join( th2, NULL);
  pthread_join( th3, NULL);
  
  return 0;
}
