#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include "ejemplo2.h"

int main( int argc, char* argv[]){

  int fd; 
  struct ticketsys * t;
  int sold, selling;
  
  fd = shm_open( SHM_NAME, O_RDWR, 0);
  if( fd == -1){ 
    perror( "Error creating shared memory object");
    exit( -1);
  } 
  
  t = (struct ticketsys *) mmap( NULL, sizeof( struct ticketsys), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if( t == MAP_FAILED){
    perror( "Error mapping shared memory object");
    exit( -1);
  }
    
  sold = 0; selling = 1;
  while( selling == 1){
    if( t->ntickets > 0){
      t->ntickets--;
      sold++; 
      usleep(100); /* active delay */
    }
    else{
      selling = 0;
    }
  }
      
  t->soldtickets += sold;
  t->cash += t->tprice * sold;

  printf("I sold %d tickets. Total sold: %d, remaining: %d. Total cash: %ld.\n", 
          sold, t->soldtickets, t->ntickets, t->cash);

  return 0;
}


/*
# lab8/ejemplos on main U:2 ?:1 with changes 
> ./ejemplo2_sell 
I sold 54802 tickets. Total sold: 54802, remaining: 0. Total cash: 548020.

> ./ejemplo2_sell 
I sold 45232 tickets. Total sold: 100034, remaining: 0. Total cash: 1000340.
*/