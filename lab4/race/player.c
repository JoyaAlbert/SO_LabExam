#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "player.h"

void player( void){

  int race_time, step_time=STEP_TIME;

  srand( getpid());
  race_time = MIN_TIME + rand() % VAR_TIME;

  while( race_time > 0){ 
    if( rand() % 1000000 < PROB_FAIL_PER_SEC*step_time/1000000)
      *(int *)NULL = 0; /* CRASH!! */
    if( rand() % 1000000 < PROB_RETIRE_PER_SEC*step_time/1000000)
      exit( 1); /* Retired! */
    usleep( race_time > step_time ? step_time : race_time);
    race_time -= step_time;
  }
  exit( 0); /* Finish! */
}
