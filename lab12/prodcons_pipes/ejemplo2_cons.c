#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include "ejemplo2.h"

int consume_item( unsigned int data);

int main( int argc, char* argv[]){

  int fd; 

  fd = open( FIFO_NAME, O_RDONLY);
  if( fd == -1){
    perror( "Error opening FIFO");
    exit( -1);
  }

  unsigned int thedata;
  int retval;

  do{ 
    if( read( fd, &thedata, sizeof( unsigned int)) == 0)
        break; /* FIFO was closed in the writing end */
    retval = consume_item( thedata);
    if( retval == -1){
      printf("Sequence error!! Terminating.\n");
      exit( -1);
    }   
  } while( 1); 

  return 0;
}

int consume_item( unsigned int data){

  static unsigned int refdata = 1;

  if( data == refdata){
    if( data % 10000 == 0)  
      printf("Got expected data: %u\n", data);
  }
  else{
    printf("Corrupt data!! Expected %u, got %u!\n", refdata, data);
    return( -1);
  }
  refdata++;

  if( CONS_DELAY_US) usleep( CONS_DELAY_US);

  return 0;
}

