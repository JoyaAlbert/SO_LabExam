#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

//cambia imagen porceso por el exceve pero mismo proceso
/** 
int main( char argc, char* argv[]){

  char * myargv[] = { "ejemplo6b", "Uno", "Dos", "Tres", "Catorce!", NULL};
  char * myenv[] = { NULL};

  printf("Me. (PID: %d)\n", getpid() );

  if( execve( "./ejemplo6b", myargv, myenv) == -1){
    perror( "Error lanzando el programa de ejemplo.");
    exit( -1);
  }

  return 0;
}
*/
//MODIFICACION genra proceso nuevo hijo para el exceve distinto PID

int main( char argc, char* argv[]){

	pid_t pid;
	int status;
  char * myargv[] = { "ejemplo6b", "Uno", "Dos", "Tres", "Catorce!", NULL};
  char * myenv[] = { NULL};

  printf("Me. (PID: %d)\n", getpid() );
	pid = fork();
	if (pid == 0)
	{
		if( execve( "./ejemplo6b", myargv, myenv) == -1){
			perror( "Error lanzando el programa de ejemplo.");
			exit( -1);
		}
	}
	else if (pid > 0) {
		wait(&status);
		if (WIFEXITED(status))
			printf("Hijo finalizado con estado %d\n", WEXITSTATUS(status));
		else
			printf("Hijo finalizado anormalmente\n");
	}
	else {
		perror("fork");
		return -1;
	}

  return 0;
}
