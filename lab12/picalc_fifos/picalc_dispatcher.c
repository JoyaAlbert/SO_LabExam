#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "picalc_pipes.h"

int main( int argc, char* argv[]){

  int workfd;
  long nwp, nstep;

  if( argc < 4){ 
    printf("Incorrect arguments. Usage:\n");
    printf("%s <integral divisions> <number of work packages> <work FIFO>\n", argv[0]);
    printf("\nTerminating.\n");
    return( -1);
  }

  nstep = atol(argv[1]);
  nwp = atol(argv[2]);

  if( /* TO-DO: Open the work pipe */ ( workfd = open( argv[3], O_WRONLY)) == -1){
    perror("Error opening work pipe.");
    exit( -1);
  }

  /* TO-DO: Invoke function that models process behaviour */
  dispatcher( workfd, nwp, nstep);

  /* TO-DO: When done, close the pipe descriptors   */
  close( workfd);

  return 0;
}
