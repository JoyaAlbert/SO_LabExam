#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define START_VAL 100000000

void mysighandler( int n);

int main( int argc, char* argv[]){

    long i, j;

    struct sigaction a;

    a.sa_handler = mysighandler;
    sigemptyset( &a.sa_mask);
    a.sa_flags = 0;

    sigaction( SIGINT, &a, NULL);

    for( i = START_VAL; ; i++){
      for( j = 2 ; j < i; j++)
        if ((i % j) == 0)
          break;
      if( j == i)
        printf("%ld\n", i); 
    }   

    return 0;
}

void mysighandler( int n){

    printf("It is a good day to die... but the day is not yet over.\n");
    signal( SIGINT, SIG_DFL);
}

