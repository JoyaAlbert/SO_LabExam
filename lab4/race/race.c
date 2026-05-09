#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include "player.h"

int main( int argc, char* argv[]){

  struct timeval start, lap;
  int i, players, pid, status, position, laptime;

  if( argc < 2){ 
    printf("Número de argumentos insuficiente.\n");
    printf("Uso: %s <num corredores>\n", argv[0]);
    return -1; 
  }

  players = atoi( argv[1]);

  printf("La carrera empieza... ahora!\n");
  gettimeofday( &start, NULL);

  for( int i = 0; i < players; i++){
    pid = fork();
    if( pid < 0){
      perror("fork");
      return -1;
    }
    if( pid == 0)
      player();
  }
      
  for( i = 0, position = 1; i < players; i++){
    pid = wait( &status);
    gettimeofday( &lap, NULL);
    laptime = (lap.tv_sec-start.tv_sec)*1000000+(lap.tv_usec-start.tv_usec);
    if( WIFEXITED( status)){
      switch( WEXITSTATUS( status)){
        case 0:
          if( position == 1)
            printf("GANADOR el proceso %d, con un tiempo de %dus!!\n", pid, laptime);
          else
            printf("En posición %d, el proceso %d, con un tiempo de %dus.\n", position, pid, laptime);
          position++;
          break;
        case 1:
            printf("El proceso %d se ha retirado a los %dus de carrera!!\n", pid, laptime);
            break;
      }   
    } else{
      printf("NOOO! El proceso %d ha tenido un accidente a los %dus de carrera!!\n", pid, laptime);
    }
    fflush( stdout);
  }
  printf("FIN DE LA CARRERA!\n");

  return 0;
}
