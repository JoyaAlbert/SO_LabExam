#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <openssl/sha.h>
#include "foominerlib.h"

uint32_t hashes = 0;

void printdigest( unsigned char* md, unsigned int dlen){

  for( int i = 0; i < dlen; i++)
    printf("%02x", md[i]);
  printf("\n");
}

int leadingzeroes( unsigned char * md, unsigned int dlen){

  int zeroes = 0;
  unsigned char bitmask = 0x80;

  for( int i = 0; i < dlen; i++) {
    if( md[i] == 0) {
      zeroes +=8;
    }   
    else {
      while( (md[i] & bitmask) == 0) {
        zeroes++;
        bitmask >>= 1;
      }   
      break;
    }   
  }
  return zeroes;
}

int fooblock_load( const char* filename, struct fooblock * b) {

  int fd; 

  if( (fd = open( filename, O_RDONLY)) == -1){
    perror("Error opening fooblock file");
    return -1; 
  }
  memset( b, 0, FOOBLOCK_LEN);
  read( fd, b, FOOBLOCK_LEN);
  close( fd);
  return 0;
}

int fooblock_save_solved( const char* filename, struct fooblock * b, uint32_t nonce) {
    
  int fd; 
  char solved_filename[100];
  
  strcpy( solved_filename, filename);
  strcat( solved_filename, ".solved");

  if( (fd = open( solved_filename, O_WRONLY | O_CREAT, 0644)) == -1){
    perror("Error opening fooblock solution file");
    return -1;
  }
  b->nonce = nonce;
  write( fd, b, FOOBLOCK_LEN);
  close( fd);
  return 0;
}

int fooblock_mine( struct fooblock * block, int difficulty, uint32_t nstart, uint32_t nend, uint32_t * nonce) {

  int lz;
  unsigned char md[ SHA256_DIGEST_LENGTH];

  for( uint32_t n = nstart; n <= nend; n++)
  {
    block->nonce = n;
    SHA256( (unsigned char *)block, FOOBLOCK_LEN, md);
    hashes++;
    lz = leadingzeroes( md, SHA256_DIGEST_LENGTH);
    if( lz >= difficulty){
      *nonce = n;
      return 0;
    }
  }
  return 1;
}

int fooblock_check( struct fooblock * b, int difficulty){

  unsigned char md[ SHA256_DIGEST_LENGTH];
  int lz;

  SHA256( (unsigned char *)b, FOOBLOCK_LEN, md);
  lz = leadingzeroes( md, SHA256_DIGEST_LENGTH);
  if( lz >= difficulty){
    printf("Block successfully checked.\n");
    printf("SHA256 digest: ");
    printdigest(md, SHA256_DIGEST_LENGTH);
    printf("SHA256 Leading zeroes: %d\n", lz);
    printf("Nonce: %u\n", b->nonce);
    return 0;
  }
  else{
    printf("Check failed.\n");
    printf("SHA256 Leading zeroes: %d\n", lz);
    return -1;
  }
}
