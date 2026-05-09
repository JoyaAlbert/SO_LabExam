#include <stdint.h>

#define FOOBLOCK_LEN  64
#define FOOBLOCK_PAYLOAD_LEN (FOOBLOCK_LEN-sizeof(uint32_t))

extern uint32_t hashes;

struct fooblock {
  unsigned char payload[FOOBLOCK_PAYLOAD_LEN];
  uint32_t nonce;
};

void printdigest( unsigned char* md, unsigned int dlen);
int leadingzeroes( unsigned char * md, unsigned int dlen);
int fooblock_load( const char* filename, struct fooblock * block);
int fooblock_save_solved( const char* filename, struct fooblock * b, uint32_t nonce);
int fooblock_mine( struct fooblock * block, int difficulty, uint32_t nstart, uint32_t nend, uint32_t * nonce);
int fooblock_check( struct fooblock * b, int difficulty);
