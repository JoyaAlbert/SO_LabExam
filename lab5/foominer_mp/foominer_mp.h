#include "foominerlib.h"
#define FOOMINER_NONCE_START 0
#define FOOMINER_NONCE_END UINT32_MAX

#define FOOMINER_MINER_PROG "foominer"

struct foominer_data{
  pid_t pid;
  uint32_t nonce_start;
  uint32_t nonce_end;
};

int foominer_exec( char * blockfile, int difficulty, struct foominer_data * miner);
void foominer_distribute_workload( uint32_t nonce_start, uint32_t nonce_end, struct foominer_data * miner, int nminers);
int foominer_miner_ended( int pid, struct foominer_data * miner, int nminers);
void foominer_miner_kill_remaining( struct foominer_data * miner, int nminers);
