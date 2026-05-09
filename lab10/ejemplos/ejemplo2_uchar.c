#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	unsigned char data;

	fd = open("myfile.bin", O_RDONLY);
	if (fd == -1) {
		perror("Error opening file");
		exit(-1);
	}

	lseek(fd, 65, SEEK_SET);

	for (int i = 0; i < 26; i++) {
		read(fd, &data, sizeof(unsigned char));
		printf("%c", data);
	}
	printf("\n");

	lseek(fd, 6, SEEK_CUR);

	for (int i = 0; i < 26; i++) {
		read(fd, &data, sizeof(unsigned char));
		printf("%c", data);
	}
	printf("\n");

	close(fd);

	return 0;
}
