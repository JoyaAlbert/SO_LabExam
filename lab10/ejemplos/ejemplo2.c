#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int argc, char* argv[]){

  int fd, data;

  fd = open( "myfile.bin", O_RDONLY);
  if( fd == -1){
    perror("Error opening file");
    exit( -1);
  }

  while( read( fd, &data, sizeof( int)) != 0)
    printf("%d\n", data);

  close( fd);

  return 0;
}

/*lab10/ejemplos on main U:5 ?:3 with changes 
> hexdump -C myfile.bin
00000000  01 00 00 00 02 00 00 00  03 00 00 00 04 00 00 00  |................|
00000010  05 00 00 00 06 00 00 00  07 00 00 00 08 00 00 00  |................|
00000020  09 00 00 00 0a 00 00 00                           |........|
00000028*/

/*lab10/ejemplos on main U:5 ?:3 with changes 
> ./ejemplo2
1
2
3
4
5
6
7
8
9
10*/