#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include "foominerlib.h"
    
int main( int argc, char* argv[])
{ 
  char * filename;
  int difficulty, retval;
  struct fooblock b;

  if( argc < 3){
    printf("Too few arguments.\nUsage:\n"); 
    printf("%s <solved block file> <difficulty>\n", argv[0]);
    return -1;
  }
    
  filename = argv[1]; 
  difficulty = atoi( argv[2]);

  retval = fooblock_load( filename, &b);
  if( retval == -1)
    return -1;

  retval = fooblock_check( &b, difficulty);
    
  return retval;
} 
