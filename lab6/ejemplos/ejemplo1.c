#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * thread_func( void * arg){

  char * msg = (char *) arg;

  while( 1){ 
    usleep( rand() % 3000000);
    puts( msg);
  }
}

int main( int argc, char* argv[]){

  pthread_t th1, th2, th3;

  pthread_create( &th1, NULL, thread_func, "Hello!");
  pthread_create( &th2, NULL, thread_func, "Hola!");
  pthread_create( &th3, NULL, thread_func, "Namaste!");

  sleep( 10);
  
  return 0;
}

