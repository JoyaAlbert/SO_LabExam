#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define SHM_NAME "/my_shm"
#define SHM_STRBUF_SIZE 80

int main( int argc, char* argv[]){

  int fd; 
  char * strbuf;

  if( argc < 2){ 
    printf("Invalid arguments. Usage:\n");
    printf("%s <String to write to shared memory>\n", argv[0]);
    exit( -1);
  }

  fd = shm_open( SHM_NAME, O_RDWR, 0);
  if( fd == -1){
    perror( "Error opening shared memory object");
    exit( -1);
  }

  strbuf = (char *) mmap( NULL, SHM_STRBUF_SIZE, PROT_WRITE, 
                          MAP_SHARED, fd, 0);
  if( strbuf == MAP_FAILED){
    perror( "Error mapping shared memory object");
    exit( -1);
  }

  strcpy( strbuf, argv[1]);

  return 0;
}

