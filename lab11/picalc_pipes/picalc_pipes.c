#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "picalc_pipes.h"

int main( int argc, char* argv[]){

  long nstep, nwp, nworkers;
  int workfd[2], resultfd[2];

  if( argc < 4){ 
    printf("Incorrect arguments. Usage:\n");
    printf("%s <integral divisions> <number of work packages> <number of worker processes>\n", argv[0]);
    printf("\nTerminating.\n");
    return( -1);
  }

  nstep = atol(argv[1]);
  nwp = atol(argv[2]);
  nworkers = atol(argv[3]);

  if( pipe( workfd) ){
    perror("Error creating work pipe.");
    exit( -1);
  }
  if( pipe( resultfd) ){
    perror("Error creating results pipe.");
    exit( -1);
  }

  /* TO-DO: Create process to model gatherer                */
  /* TO-DO: In the new process,                             */
  /* TO-DO: - Close unused pipe descriptors                 */
  /* TO-DO: - Invoke function that models process behaviour */
  /* TO-DO: - When done, close remaining pipe descriptors   */
  /* TO-DO: - And terminate process                         */
  if(fork() == 0){
    close( workfd[0]); // cierras entrada de trabajo porque aqui no se usa
    close(workfd[1]); // cierras salida de trabajo porque el gatherer no reparte
    close(resultfd[1]); // cierras salida de resultados porque aqui solo se lee
    gatherer( resultfd[0]);
    close( resultfd[0]); // cierras entrada de resultados cuando ya ha terminado
    exit( 0);
  }

  for( int i = 0 ; i < nworkers; i++){
  /* TO-DO: Create processes to model workers               */
  /* TO-DO: In each of the new processes,                   */
  /* TO-DO: - Close unused pipe descriptors                 */
  /* TO-DO: - Invoke function that models process behaviour */
  /* TO-DO: - When done, close remaining pipe descriptors   */
  /* TO-DO: - And terminate process                         */
    if(fork() == 0){
      close( workfd[1]); // cierras salida de trabajo porque el worker no reparte
      close( resultfd[0]); // cierras entrada de resultados porque el worker no recoge
      worker(workfd[0], resultfd[1]);
      close( workfd[0]); // cierras entrada de trabajo cuando ya ha leido su parte
      close( resultfd[1]); // cierras salida de resultados cuando ya ha escrito
      exit( 0);
    }
  }

  /* TO-DO: Create process to model dispatcher              */
  /* TO-DO: In the new process,                             */
  /* TO-DO: - Close unused pipe descriptors                 */
  /* TO-DO: - Invoke function that models process behaviour */
  /* TO-DO: - When done, close remaining pipe descriptors   */
  /* TO-DO: - And terminate process                         */
  if( fork() == 0){
    close( workfd[0]); // cierras entrada de trabajo porque el dispatcher no lee
    close( resultfd[0]); // cierras entrada de resultados porque aqui no se leen
    close(resultfd[1]); // cierras salida de resultados porque el dispatcher no escribe
    dispatcher(workfd[1], nwp, nstep);
    close( workfd[1]); // cierras salida de trabajo cuando ya ha enviado todo
    exit(0);
  }


  /* TO-DO: Close all pipe descriptors. (Why?)              */
  close(workfd[0]); // cierras entrada de trabajo porque el padre no la usa
  close(workfd[1]); // cierras salida de trabajo porque el padre no reparte
  close(resultfd[0]); // cierras entrada de resultados porque el padre no recoge
  close(resultfd[1]); // cierras salida de resultados porque el padre no escribe

  /* TO-DO: Wait for all processes to finish                */
  for(int i = 0; i < nworkers + 2; i++)
    wait(NULL);

  return(0);
}
