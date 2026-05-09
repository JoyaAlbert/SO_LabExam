#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ARRAY_SIZE 10

int main(void)
{
	int myarray[ARRAY_SIZE];
	int fd;
	int data;
	int size;

	fd = open("myfile.bin", O_RDWR);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(-1);
	}

	size = lseek(fd, 0, SEEK_END);
	if (size == 0)
		data = 0;
	else
	{
		lseek(fd, -sizeof(int), SEEK_END);
		read(fd, &data, sizeof(int)) != sizeof(int);
	}

	lseek(fd, 0, SEEK_END);

	for (int i = 0; i < ARRAY_SIZE; i++)
		myarray[i] = data + i + 1;

	write(fd, myarray, ARRAY_SIZE * sizeof(int));
	close(fd);
	return (0);
}
