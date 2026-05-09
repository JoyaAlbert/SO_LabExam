#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include "foominerlib.h"

int main( int argc, char* argv[]){

  int difficulty;
  uint32_t nonce_start, nonce_end, nonce_sol;
  struct fooblock b;
  char * blockfile;

  if( argc < 5){ 
    printf("Too few arguments.\nUsage:\n");
    printf("%s <block file> <difficulty> <nonce start> <nonce end>\n", argv[0]);
    return -1; 
  }

  blockfile = argv[1];
  difficulty = atoi( argv[2]);
  nonce_start = (uint32_t) atol( argv[3]);
  nonce_end = (uint32_t) atol( argv[4]);

  if( fooblock_load( blockfile, &b) == -1)
    return -1;
    
  if( fooblock_mine( &b, difficulty, nonce_start, nonce_end, &nonce_sol) == 0){
    printf("(%d) found nonce %u is valid.\n", getpid(), nonce_sol);
    fooblock_save_solved( blockfile, &b, nonce_sol);
    return 0;
  }
  printf("(%d) Nonce not found.\n", getpid());
  return 1;
}
