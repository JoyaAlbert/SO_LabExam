#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include "ejemplo2.h"

unsigned int produce_item( void);

int main( int argc, char* argv[]){

  int fd;
  unsigned int newdata;

  mkfifo( FIFO_NAME, 0600);
  fd = open( FIFO_NAME, O_WRONLY);
  if( fd == -1){
    perror( "Error opening FIFO");
    exit( -1);
  }

  do{
    newdata = produce_item();
    write( fd, &newdata, sizeof( unsigned int));
  }while(1);

  return 0;
}

unsigned int produce_item( void){

  static unsigned int data = 0;

  if( PROD_DELAY_US) usleep( PROD_DELAY_US);

  return ++data;
}

