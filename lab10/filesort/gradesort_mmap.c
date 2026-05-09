#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include "filesort.h"

int gradesort( int fd) 
{
  int i, j, nswaps = 0, nelem, swap;
  struct evaluation *pe, temp;
  struct stat s;

  /* TO-DO: Obtain file size */
  fstat( fd, &s);
  /* TO-DO: Map the file */
  pe = mmap( NULL, s.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if( pe == MAP_FAILED)
  {   
    perror("Error mapping file");
    exit( -1);
  }

  /* TO-DO: Calculate the number of items in the file */
  nelem = s.st_size / sizeof( struct evaluation);
  for( i=0; i < nelem-1 ; i++){
    swap = 0;
    for( j=0 ; j<nelem-i-1; j++)
      if(  pe[j].avgrade < pe[j+1].avgrade )
      {   
        /* TO-DO: Swap the items */
        temp = pe[j];
        pe[j] = pe[j+1];
        pe[j+1] = temp;

        swap = 1;
        nswaps++;
      }   
    if( swap == 0)
      break;
  }
  
  /* TO-DO: Unmap the file */
  munmap( pe, s.st_size);
  return nswaps;
}

/*
> ./filesort_mmap datos.bin 
Swaps: 13989
Elapsed time: 13720us
# lab10/filesort on main U:9 ?:2 with changes 
> make datos 
tar -xzf datos.tgz
# lab10/filesort on main U:9 ?:2 with changes 
> ./filesort_std datos.bin
Swaps: 13989
Elapsed time: 494755us
*/
