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
    sem_wait(&t->sem);
    if( t->ntickets > 0){
      t->ntickets--;
      sold++; 
      sem_post(&t->sem);
      usleep(100);
    }
    else{
      sem_post(&t->sem);
      selling = 0;
    }
  }
      
  sem_wait(&t->sem);
  t->soldtickets += sold;
  t->cash += t->tprice * sold;
  sem_post(&t->sem);

  printf("I sold %d tickets. Total sold: %d, remaining: %d. Total cash: %ld.\n", 
          sold, t->soldtickets, t->ntickets, t->cash);

  return 0;
}
