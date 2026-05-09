#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main( int argc, char* argv[]){

  int myfd, n;

  myfd = open( "myfifo", O_RDONLY);
  while( read( myfd, &n, sizeof( int) ) > 0)
    printf("Received: %d\n", n); 
  printf("The other end of the pipe has been closed. Terminating.\n");
  close( myfd);
  return 0;
}
