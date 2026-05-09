#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "filesort.h"

int gradesort( int fd) 
{
  int i, j, nswaps = 0, nelem, swap;
  struct evaluation e1, e2; 
  struct stat s;

  /* TO-DO: Obtain file size */
  fstat( fd, &s);
  /* TO-DO: Calculate the number of items in the file */
  nelem = s.st_size / sizeof( struct evaluation);
  for( i=0; i < nelem-1; i++)
  {
    swap = 0;
    /* TO-DO: Set file offset at beginning of file for each pass */
    lseek( fd, 0, SEEK_SET);
    for( j=0; j<nelem-i-1; j++)
    {   
      /* TO-DO: Read the next two items from file */
      read( fd, &e1, sizeof( struct evaluation));
      read( fd, &e2, sizeof( struct evaluation));
      if(e1.avgrade < e2.avgrade)
      {   
        /* TO-DO: Save the two items in the file swapping their positions */
        lseek( fd, -2*sizeof( struct evaluation), SEEK_CUR);
        write( fd, &e2, sizeof( struct evaluation));
        write( fd, &e1, sizeof( struct evaluation));
        lseek( fd, -sizeof( struct evaluation), SEEK_CUR);
    
        swap=1;
        nswaps++;
      }
      else /* TO-DO: Set file offset at the correct position for next read */
        lseek( fd, -sizeof( struct evaluation), SEEK_CUR);
      
    }   
    if( swap == 0)
      break;
  }
  
  return nswaps;
}
