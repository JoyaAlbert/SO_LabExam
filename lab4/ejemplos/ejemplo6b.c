#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main( char argc, char* argv[]){

  printf("Me too. (PID: %d)\n", getpid() );

  for( int i = 1; i < argc; i++)
    printf("%s%s", 
      argv[i], 
      i + 1 != argc ? ", " : ".\n"
    );

  return 0;
}
