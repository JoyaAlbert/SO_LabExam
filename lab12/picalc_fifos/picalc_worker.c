#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "picalc_pipes.h"

int main( int argc, char* argv[]){

  int workfd;
  int resultfd;
  int perm = 0;

  if( argc < 3){ 
    printf("Incorrect arguments. Usage:\n");
    printf("%s <work FIFO> <results FIFO> [<p>ermanent]\n", argv[0]);
    printf("\nTerminating.\n");
    return( -1);
  }

  if( argc == 4)
    if( strcmp( argv[3], "p") == 0)
      perm = 1;

  do{
    if( /* TO-DO: Open the work pipe */ ( workfd = open( argv[1], O_RDONLY)) == -1){
      perror("Error opening work pipe.");
      exit( -1);
    }   
  
    if( /* TO-DO: Open the results pipe */ ( resultfd = open( argv[2], O_WRONLY)) == -1){
      perror("Error opening results pipe.");
      exit( -1);
   }

  /* TO-DO: Invoke function that models process behaviour */
  worker( workfd, resultfd);

  /* TO-DO: When done, close the pipe descriptors   */
  close( workfd);
  close( resultfd);
  } while( perm == 1);

  return 0;
}
