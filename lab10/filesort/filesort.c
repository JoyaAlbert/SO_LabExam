#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include "filesort.h"

int main( int argc, char* argv[])
{
  int fd; 
  int n, tdelta;
  struct timeval t1, t2; 

  if( argc <2) 
  {
    printf("Invalid arguments. Usage:\n");
    printf("%s <file>\n", argv[0]);
    exit(-1);
  }

  if( (fd = open( argv[1], O_RDWR)) == -1) 
  {
    perror("Error opening file");
    exit( -1);
  }

  gettimeofday( &t1, NULL);
  n = gradesort( fd);
  gettimeofday( &t2, NULL);

  tdelta = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
  printf( "Swaps: %d\n", n); 
  printf( "Elapsed time: %dus\n", tdelta);

  close( fd);

  return 0;
}
