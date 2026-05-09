#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	pid_t pid;
    int status, value;

	if ((pid = fork()) != 0) {
		printf("Padre: esperando a que finalice el proceso hijo...\n");
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
			value = WEXITSTATUS(status);
			if (value != 1)
				printf("Padre: hijo (%d) finalizado con estado %d.\n", pid, value);
			else
				printf("Padre: hijo (%d) finalizado con estado %d.\n", pid, value);
		} else {
			printf("Padre: hijo (%d) finalizado anormalmente\n", pid);
		}
	} else {
		printf("Hijo: durmiendo unos segundos...\n");
		sleep(1);
		srand( getpid()); /* Initialize pseudorandom number generator */
		int d = rand() % 3; /* Asigna a d un n. aleatorio entre 0 y 2) */
		printf("Hijo: calculando 100/%d = %d y finalizando.\n", d, 100/d);

		exit(1);
	}

	return 0;
}
