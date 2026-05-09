#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main( int argc, char* argv[]){

  long nworkers;

  char workfifopath[]   = "work";
  char resultfifopath[] = "result";

  char dispatcherpath[] = "./picalc_dispatcher";
  char gathererpath[]   = "./picalc_gatherer";
  char workerpath[]     = "./picalc_worker";

  if( argc < 4){ 
    printf("Incorrect arguments. Usage:\n");
    printf("%s <integral divisions> <number of work packages> <number of worker processes>\n", argv[0]);
    printf("\nTerminating.\n");
    return( -1);
  }

  nworkers = atol(argv[3]);

  /* TO-DO: Create work and results FIFOs                             */
  unlink( workfifopath);
  unlink( resultfifopath);

  if( mkfifo( workfifopath, 0666) == -1){
    perror( "Error creating work FIFO");
    exit( -1);
  }

  if( mkfifo( resultfifopath, 0666) == -1){
    perror( "Error creating results FIFO");
    exit( -1);
  }

  /* TO-DO: Create process to launch gatherer                         */
  if( fork() == 0){
  /* TO-DO: In the new process,                                       */
    char * g_argv[] = { gathererpath, resultfifopath, NULL } ;
    char * g_envp[] = { NULL};
  /* TO-DO: - Execute the program that models the process behaviour   */
    execve( gathererpath, g_argv, g_envp);
  /* TO-DO: - Is there anything else to do after? */
    perror( "Error executing gatherer");
    exit( -1);
  }

  for( int i = 0 ; i < nworkers; i++){
  /* TO-DO: Create process to launch worker                           */
    if( fork() == 0){
  /* TO-DO: In the new process,                                       */
    char * w_argv[] = { workerpath, workfifopath, resultfifopath, NULL } ;
    char * w_envp[] = { NULL};
  /* TO-DO: - Execute the program that models the process behaviour   */
      execve( workerpath, w_argv, w_envp);
  /* TO-DO: - Is there anything else to do after? */
      perror( "Error executing worker");
      exit( -1);
    }
  }

  /* TO-DO: Create process to launch dispatcher                       */
  if( fork() == 0){
  /* TO-DO: In the new process,                                       */
    char * d_argv[] = { dispatcherpath, argv[1], argv[2], workfifopath, NULL } ;
    char * d_envp[] = { NULL};
  /* TO-DO: - Execute the program that models the process behaviour   */
    execve( dispatcherpath, d_argv, d_envp);
  /* TO-DO: - Is there anything else to do after? */
    perror( "Error executing dispatcher");
    exit( -1);
  }

  /* TO-DO: Wait for all processes to finish                          */
  for( int i = 0; i < nworkers + 2; i++)
    wait( NULL);

  unlink( workfifopath);
  unlink( resultfifopath);

  return(0);
}
