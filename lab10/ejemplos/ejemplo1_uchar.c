#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ARRAY_SIZE 256

int main( int argc, char* argv[]){

  unsigned char myarray[ ARRAY_SIZE];

  for( int i = 0; i < ARRAY_SIZE; i++)
    myarray[ i] = i;

  int fd; 

  fd = open( "myfile.bin", O_WRONLY | O_CREAT, 0600);
  if( fd == -1){
    perror("Error creating file");
    exit( -1);
  }

  write( fd, myarray, ARRAY_SIZE*sizeof( unsigned char));
  
  close( fd);

  return 0;
}
