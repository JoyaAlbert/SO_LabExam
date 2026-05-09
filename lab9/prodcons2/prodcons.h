#include <semaphore.h>

#define SHM_NAME "/my_shm"
#define PROD_DELAY_US 0
#define CONS_DELAY_US 0
#define BUFFER_SIZE 10

struct txfer_data {
  int count;
  unsigned int in; 
  unsigned int out;
  unsigned int buffer[BUFFER_SIZE];
  sem_t mutex; 
  sem_t empty;
  sem_t full;
};
