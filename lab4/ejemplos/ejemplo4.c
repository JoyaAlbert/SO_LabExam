#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	pid_t pid;
    int status;

	if ((pid = fork()) != 0) {
		printf("Padre: esperando a que finalice el proceso hijo...\n");
		waitpid(pid, &status, 0);
		printf("Padre: hijo (%d) finalizado con estado %d.\n", pid, WEXITSTATUS(status));
	} else {
		printf("Hijo: durmiendo unos segundos...\n");
		sleep(1);
		printf("Hijo: finalizando.\n");
        exit(1);
	}

	return 0;
}