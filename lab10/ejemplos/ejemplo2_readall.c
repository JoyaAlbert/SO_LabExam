#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	struct stat s;

	fd = open("myfile.bin", O_RDONLY);
	if (fd == -1) {
		perror("Error opening file");
		exit(-1);
	}

	fstat(fd, &s);

	int n = s.st_size / sizeof(int);
	int myarray[n];

	read(fd, myarray, s.st_size);

	for (int i = 0; i < n; i++)
		printf("%d\n", myarray[i]);

	close(fd);

	return 0;
}