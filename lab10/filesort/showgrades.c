#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "filesort.h"

int main( int argc, char* argv[])
{
  int fd; 
  struct evaluation e;
  struct stat s;
  int i;

  if( argc <2) 
  {
    printf("Invalid arguments. Usage:\n");
    printf("%s <file>\n", argv[0]);
    exit(-1);
  }

  if( (fd = open( argv[1], O_RDONLY)) == -1) 
  {
    perror("Error opening file");
    exit( -1);
  }

  fstat( fd, &s);

  for( i = 0; i < s.st_size/sizeof(struct evaluation); i++){
    read( fd, &e, sizeof( struct evaluation));
    printf("%10s:%5.2f:%5.2f:%5.2f:%s %s, %s\n",
      e.id,
      e.grade1, e.grade2, e.avgrade,
      e.surname1, e.surname2, e.name);
  }

  close( fd);

  return 0;
}
