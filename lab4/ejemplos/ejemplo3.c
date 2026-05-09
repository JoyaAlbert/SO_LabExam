#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char* argv[]){

    pid_t pid1, pid2;
    
    if( (pid1=fork()) != 0){ 
      if( (pid2=fork()) != 0){ 
        printf("Padre: esperando a que acabe el Hijo 1...\n");
        waitpid(pid1, NULL, 0);
        printf("Padre: Hijo 1 finalizado. Esperando a que acabe el Hijo 2...\n");
        waitpid(pid2, NULL, 0);
        printf("Padre: Hijo 2 finalizado. THE END.\n");
      } else {
        printf("Hijo 2: durmiendo unos segundos...\n");
        srand( getpid());    /* Initialize pseudorandom number generator */
        sleep( 1+rand()%3 ); /* Sleep for 1-3 seconds */
        printf("Hijo 2: despertado y finalizando.\n");
      }   
    } else {
        printf("Hijo 1: durmiendo unos segundos...\n");
        srand( getpid());
        sleep( 1+rand()%3 );  
        printf("Hijo 1: despertado y finalizando.\n");
    }   

    return 0;
}
