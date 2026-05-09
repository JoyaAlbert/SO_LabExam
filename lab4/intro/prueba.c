#include<stdio.h>
#include<errno.h>
#include<fcntl.h>

int fd; 

int main( int argc, char* argv[]){

  if( argc < 2){ 
    printf("Missing argument.\n");
    printf("Usage: %s <filename>\n", argv[0]);
    return -1;
  }

  fd = open(argv[1], O_RDWR | O_CREAT, 0666);
  if(fd < 0) { /* If there's an error opening the file */
    if( errno == ENOENT)
      printf("File does not exist.\n");
    else if( errno == EEXIST)
      printf("File already exists.\n");
    else if( errno == EACCES)
      printf("No permission to open the file.\n");
    return -1;
  }
  printf("File opened successfully.\n");
  return 0;
}
