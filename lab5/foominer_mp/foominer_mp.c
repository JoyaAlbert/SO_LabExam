#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include "foominer_mp.h"

int main( int argc, char* argv[])
{
  int difficulty, nminers, status;
  char * blockfile;
  uint32_t nonce_start = FOOMINER_NONCE_START, nonce_end=FOOMINER_NONCE_END;
  pid_t pid;

  if( argc < 4){
    printf("Too few arguments.\nUsage:\n");
    printf("%s <block file> <difficulty> <num miners>\n", argv[0]);
    return -1;
  }

  blockfile = argv[1];
  difficulty = atoi( argv[2]);
  nminers = atoi( argv[3]);

  struct foominer_data miner[nminers];

  foominer_distribute_workload( nonce_start, nonce_end, miner, nminers);

  for( int i = 0; i < nminers; i++){
    miner[i].pid = fork();

    if( miner[i].pid == -1){
      foominer_miner_kill_remaining( miner, nminers);
      return -1;
    }

    if( miner[i].pid == 0){
      if( foominer_exec( blockfile, difficulty, &miner[i]) == -1)
        exit(-1);
    }
  }

  int minersrunning = nminers;

  while( minersrunning > 0){

    pid = wait(&status);
    if( pid == -1){
      foominer_miner_kill_remaining( miner, nminers);
      return -1;
    }

    minersrunning--;
    int miner_index = foominer_miner_ended( pid, miner, nminers);

    if( WIFEXITED( status)){
      switch(WEXITSTATUS(status)){
        case -1:
          printf("Miner %d (PID=%d) reports error status. Terminating others and exiting.\n", miner_index, pid);
          foominer_miner_kill_remaining( miner, nminers);
          return -1;
        case 0:
          printf("Miner %d (PID=%d) reports nonce found. Terminating other miners.\n", miner_index, pid);
          foominer_miner_kill_remaining( miner, nminers);
          return 1;
        case 1:
          printf("Miner %d (%d) reports no solution found.\n", miner_index, pid);
          break;
      }
    } 
    else {
      printf("Miner %d (%d) crashed. Terminating others and exiting.\n", miner_index, pid);
      foominer_miner_kill_remaining( miner, nminers);
      return -1;
    }
  }
  printf("All miners ended and no solution found.\n");
  return 0;
}

int foominer_exec( char * blockfile, int difficulty, struct foominer_data * miner){
  char d[16], ns[16], ne[16];
  char *argv_exec[6];

  sprintf(d, "%d", difficulty);
  sprintf(ns, "%u", miner->nonce_start);
  sprintf(ne, "%u", miner->nonce_end);

  argv_exec[0] = FOOMINER_MINER_PROG;
  argv_exec[1] = blockfile;
  argv_exec[2] = d;
  argv_exec[3] = ns;
  argv_exec[4] = ne;
  argv_exec[5] = NULL;

  execve("./" FOOMINER_MINER_PROG, argv_exec, NULL);
  return -1; 
}

void foominer_distribute_workload( uint32_t nonce_start, uint32_t nonce_end, struct foominer_data * miner, int nminers){

  uint32_t workload;

  for( int i = 0; i < nminers; i++){
    miner[i].nonce_start = nonce_start;
    workload = (nonce_end-nonce_start)/(nminers-i);
    miner[i].nonce_end = nonce_start + workload;
    nonce_start+=workload;
  }
} 

int foominer_miner_ended( int pid, struct foominer_data * miner, int nminers){
  for( int i = 0; i < nminers; i++)
    if( miner[i].pid == pid){
      miner[i].pid = 0;
      return i;
    }
  return -1;
}

void foominer_miner_kill_remaining( struct foominer_data * miner, int nminers){
	for (int i = 0; i < nminers; i++) {
		if (miner[i].pid > 0) {
			kill(miner[i].pid, SIGTERM);
			miner[i].pid = 0;
		}
	}
}
