#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int i = 0, n, espera;
	char buffer[512], prog[512];
	int fd = open(argv[1], O_RDONLY);
	pid_t pids[100]; // não é estritamente necessário, ok
	
	while ((n = readln(fd, buffer, sizeof(buffer) - 1)) > 0) {
		buffer[n] = '\0';
		sscanf(buffer, "%s %d", prog, &espera);
		if (espera != 0) {
			alarm(espera);
			pause();
		}
		if ((pids[i] = fork()) == 0) {
			execlp(prog, prog, NULL);
			perror(prog);
			_exit(1);
		}
		i++;
	}
	/* não é estritamente necessário */
	while (i != 0) {
		wait(NULL);
		i--;
	}
	return 0;
	return 0;
}
