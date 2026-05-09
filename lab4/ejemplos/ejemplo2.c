#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	pid_t pid;

	if ((pid = fork()) != 0) {
		printf("Padre: esperando a que finalice el proceso hijo...\n");
		wait(NULL);
		printf("Padre: hijo (%d) finalizado.\n", pid);
	} else {
		printf("Hijo: durmiendo unos segundos...\n");
		sleep(1);
		printf("Hijo: finalizando.\n");
	}

	return 0;
}