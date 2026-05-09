#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
// Meti el fork para q salte el BOO
int main( char argc, char* argv[]){
  pid_t pid;

  char * myargv[] = { "/bin/ls", "-l", NULL};
  char * myenv[] = { NULL};
  pid = fork();
  if (pid == 0)
  {
    if( execve( myargv[ 0], myargv, myenv) == -1){
      perror( "Error lanzando el programa de ejemplo.");
      exit( -1);
    } 
  }
  else
    wait(NULL);

  printf("Boo!!\n");

  return 0;
}

