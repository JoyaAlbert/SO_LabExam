#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int main( int argc, char* argv[]){

  int fd; 

  fd = open( "myfile.bin", O_RDONLY);
  if( fd == -1){
    perror("Error opening file");
    exit( -1);
  }

  struct stat s;

  fstat( fd, &s);

  int ndata = s.st_size/sizeof( int);

  int * array = (int *) mmap( NULL, s.st_size, PROT_READ, MAP_SHARED, fd, 0); 

  for( int i = 0; i < ndata; i++)
    printf("%d\n", array[i]);

  munmap( array, s.st_size);
  close( fd);

  return 0;
}
