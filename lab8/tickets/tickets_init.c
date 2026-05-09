#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include "tickets.h"

int main( int argc, char* argv[]){

  int fd; 
  struct ticketsys * t;

  fd = shm_open( SHM_NAME, O_CREAT | O_RDWR, 0600);
  if( fd == -1){
    perror( "Error creating shared memory object");
    exit( -1);
  }

  ftruncate( fd, sizeof( struct ticketsys));

  t = (struct ticketsys *) mmap( NULL, sizeof( struct ticketsys), 
                                 PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
  if( t == MAP_FAILED){
    perror( "Error mapping shared memory object");
    exit( -1);
  }

  t->ntickets = 100000; t->soldtickets = 0; t-> tprice = 10; t->cash = 0;
  sem_init(&t->sem, 1, 1);

  return 0;
}
