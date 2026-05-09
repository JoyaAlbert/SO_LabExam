#define SHM_NAME "/my_shm"
#define PROD_DELAY_US 10
#define CONS_DELAY_US 150
#define BUFFER_SIZE 10

struct txfer_data {
  int count;
  unsigned int in; 
  unsigned int out;
  unsigned int buffer[BUFFER_SIZE];
};
