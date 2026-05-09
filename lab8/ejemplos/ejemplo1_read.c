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

  fd = shm_open( SHM_NAME, O_RDONLY, 0); 
  if( fd == -1){
    perror( "Error opening shared memory object");
    exit( -1);
  }

  strbuf = (char *) mmap( NULL, SHM_STRBUF_SIZE, PROT_READ, 
                          MAP_SHARED, fd, 0); 
  if( strbuf == MAP_FAILED){
    perror( "Error mapping shared memory object");
    exit( -1);
  }
  while(1)
  {
    printf("%s\n", strbuf);
    sleep(1);
  }
  return 0;
}


/*
# lab8/ejemplos on main U:1 ?:1 with changes 
> ./ejemplo1_read 
Hello, world!!
# lab8/ejemplos on main U:1 ?:1 with changes 
> ./ejemplo1_write "This is a shared string!"
# lab8/ejemplos on main U:1 ?:1 with changes 
> ./ejemplo1_read 
This is a shared string!
*/

/*
lab8/ejemplos on main U:1 ?:1 with changes 
> ./ejemplo1_read 
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
This is a shared string!
esto funciona
esto funciona
esto funciona
esto funciona
esto funciona
esto funciona
esto funciona
esto funciona
esto funciona
esto funciona
esto funciona
esto funciona
esto funciona
funciona si
funciona si
funciona si
*/