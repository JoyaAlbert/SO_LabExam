#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include "ejemplo1.h"

unsigned int produce_item( void);

int main( int argc, char* argv[]){

  int fd;
  struct txfer_data * d;
  size_t memsize = sizeof( struct txfer_data);
  unsigned int newdata;

  fd = shm_open( SHM_NAME, O_CREAT | O_RDWR, 0600);
  if( fd == -1){
    perror( "Error creating shared memory object");
    exit( -1);
  }

  ftruncate( fd, memsize);

  d = (struct txfer_data *) mmap( NULL, memsize, PROT_READ | PROT_WRITE,
                                  MAP_SHARED, fd, 0);
  if( d == MAP_FAILED){
    perror( "Error mapping shared memory object");
    exit( -1);
  }

  d-> count = 0;
  d-> in = 0;
  d-> out = 0;

  do{
    newdata = produce_item();

    do{
      if( d->count != BUFFER_SIZE){
        d->count++;
        d->buffer[d->in] = newdata;
        d->in = (d->in + 1) % BUFFER_SIZE;
        break;
      }
    }while(1);
  }while(1);

  return 0;
}

unsigned int produce_item( void){

  static unsigned int data = 0;

  if( PROD_DELAY_US) usleep( PROD_DELAY_US);

  return ++data;
}
