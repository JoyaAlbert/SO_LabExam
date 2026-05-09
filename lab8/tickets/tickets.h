#define SHM_NAME "/my_shm"
#include <semaphore.h>

struct ticketsys{
  int ntickets;    /* Tickets disponibles */
  int soldtickets; /* Tickets vendidos    */
  int tprice;      /* Precio del ticket   */ 
  long cash;       /* Dinero en la caja   */
  sem_t sem;       /* Semáforo            */
};
