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

  fd = shm_open( SHM_NAME, O_CREAT | O_RDWR, 0600);
  if( fd == -1){
    perror( "Error creating shared memory object");
    exit( -1);
  }

  ftruncate( fd, SHM_STRBUF_SIZE);

  strbuf = (char *) mmap( NULL, SHM_STRBUF_SIZE, PROT_READ | PROT_WRITE, 
                          MAP_SHARED, fd, 0); 
  if( strbuf == MAP_FAILED){
    perror( "Error mapping shared memory object");
    exit( -1);
  }

  strcpy( strbuf, "Hello, world!!");
  if( munmap( strbuf, SHM_STRBUF_SIZE) == -1){
    perror( "Error unmapping shared memory object");
    exit( -1);
  }
  if( close( fd) == -1){
    perror( "Error closing shared memory object");
    exit( -1);
  }

  return 0;
}


/*
> ls -l /dev/shm
.rw-r-----. albertojoya albertojoya 4.0 KB Thu Apr  9 12:15:52 2026  lttng-ust-wait-8-1000
.rw-------. albertojoya albertojoya  80 B  Thu Apr  9 12:33:40 2026  my_shm  escritura y lectura para el propteario yo


> cat /dev/shm/my_shm 
Hello, world!!

> hexdump -C /dev/shm/my_shm 
00000000  48 65 6c 6c 6f 2c 20 77  6f 72 6c 64 21 21 00 00  |Hello, world!!..|
00000010  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000050
*/
