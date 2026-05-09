#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	pid_t pid;
	pid_t pid_padre;

	pid_padre = getpid();
	pid = fork();

	if (pid == 0) {
		pid = getpid();
		printf("Soy el hijo (%d), Mi padre es (%d ).\n", pid, pid_padre);
	} else if (pid > 0) {
		printf("Soy el Padre (%d), Mi hijo es (%d)", pid_padre, pid);
		wait(NULL);
	} else {
		perror("fork");
		return -1;
	}
	return 0;
}
