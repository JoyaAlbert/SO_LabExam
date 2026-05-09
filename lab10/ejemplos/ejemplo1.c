#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ARRAY_SIZE 10

int main( int argc, char* argv[]){

  int myarray[ ARRAY_SIZE];

  for( int i = 0; i < ARRAY_SIZE; i++)
    myarray[ i] = i+1;

  int fd; 

  fd = open( "myfile.bin", O_WRONLY | O_CREAT, 0600);
  if( fd == -1){
    perror("Error creating file");
    exit( -1);
  }

  write( fd, myarray, ARRAY_SIZE*sizeof( int));
  
  close( fd);

  return 0;
}
