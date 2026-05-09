#define SHM_NAME "/my_shm"

struct ticketsys{
  int ntickets;    /* Tickets disponibles */
  int soldtickets; /* Tickets vendidos    */
  int tprice;      /* Precio del ticket   */ 
  long cash;       /* Dinero en la caja   */
};
